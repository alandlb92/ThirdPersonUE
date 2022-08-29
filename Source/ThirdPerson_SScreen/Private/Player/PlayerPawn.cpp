// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerPawn.h"
#include "Player/Pstate.h"
#include "Player/PlayerHUD.h"
#include "Interactables/InteractableBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Player/PlayerAnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "InWorldUI/PlayerLabelIWUI.h"
#include "GameFramework/PlayerState.h"
#include "Interactables/ShowTextInteractable.h"
#include "Components/SceneComponent.h"
#include "Net/UnrealNetwork.h"
#include "Managers/PlayerManager.h"
#include "Managers/LevelManager.h"

void FPlayerPawnInput::UpdateLeftAxisX(float x)
{
	_rawLeftAxis.X = x;
}

void FPlayerPawnInput::UpdateLeftAxisY(float y)
{
	_rawLeftAxis.Y = y;
}

void FPlayerPawnInput::UpdateRightAxisX(float x)
{
	_rawRightAxis.X = x;
}

void FPlayerPawnInput::UpdateRightAxisY(float y)
{
	_rawRightAxis.Y = y;
}

void FPlayerPawnInput::Sanitize()
{
	if (Enabled)
	{
		LeftAxistState = _rawLeftAxis.ClampAxes(-1.0f, 1.0f);
		_rawLeftAxis.Set(0.0f, 0.0f);
		RightAxistState = _rawRightAxis.ClampAxes(-1.0f, 1.0f);
		_rawRightAxis.Set(0.0f, 0.0f);
	}
}


// Sets default values
APlayerPawn::APlayerPawn()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	_collider = CreateAbstractDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
	RootComponent = _collider;

	_mesh = CreateAbstractDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	_mesh->SetupAttachment(RootComponent);

	_widget3D = CreateAbstractDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	_widget3D->AddWorldRotation(FRotator(0, 0, 0));
	_widget3D->SetupAttachment(RootComponent);
	_widget3D->SetRelativeLocation(FVector(0, 0, 0));
	_widget3D->SetUsingAbsoluteRotation(true);

	_cameraSpringArm = CreateAbstractDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	_cameraSpringArm->SetupAttachment(RootComponent);
	_cameraSpringArm->TargetArmLength = 400.0f;
	_cameraSpringArm->bEnableCameraLag = true;
	_cameraSpringArm->CameraLagSpeed = 3.0f;
	_cameraSpringArm->SetRelativeLocation(FVector(0, 0, 100));

	_camera = CreateAbstractDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	_camera->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f));
	_camera->SetupAttachment(_cameraSpringArm, USpringArmComponent::SocketName);

	_maxSpeed = 600.0f;
	_maxPlayerSpeedRotation = 200.0f;
	_maxCameraSpeedRotation = 50.0f;

	bUseControllerRotationYaw = false;

	SetReplicates(true);
	SetReplicateMovement(true);
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	if (IsLocallyControlled())
		Server_SetPlayerIndex();
	Super::BeginPlay();
	Cast<ALevelManager>(GetLevel()->GetLevelScriptActor())
		->GetPlayerManager()->Register(this);
	SetActorHiddenInGame(true);
}

void APlayerPawn::StartGameplay()
{
	if (IsLocallyControlled()) {
		ConfigureInputForGamePlay();
		UGameplayStatics::GetPlayerController(this, _localPlayerIndex)->SetViewTargetWithBlend(_camera->GetOwner());
	}

	if (_widget3D)
		Cast<UPlayerLabelIWUI>(_widget3D->GetWidget())->SetLabel(FString(GetPState()->name));

	if (!HasAuthority())
		Server_OnStartGameplay(GetPState()->name);
	else if (HasAuthority()) {
		SetActorHiddenInGame(false);
		Multicast_OnStartGameplay(GetPState()->name);
	}

	if (GetPlayerState())
		UE_LOG(LogTemp, Warning, TEXT("player id: %i  added"), GetPlayerState()->GetPlayerId());
}

void APlayerPawn::Server_OnStartGameplay_Implementation(const FString& name)
{
	SetActorHiddenInGame(false);
	Multicast_OnStartGameplay(name);
}

void APlayerPawn::Multicast_OnStartGameplay_Implementation(const FString& name)
{
	if (!IsLocallyControlled())
	{
		if (_widget3D)
			Cast<UPlayerLabelIWUI>(_widget3D->GetWidget())->SetLabel(name);
		else
			UE_LOG(LogTemp, Warning, TEXT("NO WIGET 3D"));
	}
}


void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsLocallyControlled()) {
		_playerInput.Sanitize();
		CalculatePlayerXYMovement(DeltaTime);
		CalculatePlayerYawRotation(DeltaTime);
		CalculateCameraPitchRotation(DeltaTime);
		CalculateVelocity();
		SetAnimationVariables();
	}
}



void  APlayerPawn::CalculatePlayerXYMovement(float DeltaTime)
{
	FVector2D movementX = _playerInput.LeftAxistState.X * _maxSpeed * FVector2D(GetActorRightVector());
	FVector2D movementY = _playerInput.LeftAxistState.Y * _maxSpeed * FVector2D(GetActorForwardVector());
	FVector movement = FVector(movementX + movementY, 0) * DeltaTime;

	FVector newPosition = (GetActorLocation()) + movement;
	SetActorLocation(newPosition);

	if (!HasAuthority())
		Server_OnCalculatePlayerXYMovement(newPosition);
}

bool APlayerPawn::Server_OnCalculatePlayerXYMovement_Validate(FVector newPosition)
{
	//TODO
	//validate if new position acceptable range from last position
	return true;
}

void APlayerPawn::Server_OnCalculatePlayerXYMovement_Implementation(FVector newPosition)
{
	SetActorLocation(newPosition);
}


void APlayerPawn::CalculatePlayerYawRotation(float DeltaTime)
{
	float yawToAdd = _playerInput.RightAxistState.X * _maxPlayerSpeedRotation * DeltaTime;
	FQuat quatRotationToAdd = FQuat(FRotator(0, yawToAdd, 0));
	AddActorLocalRotation(quatRotationToAdd, false, 0, ETeleportType::None);
	if (!HasAuthority())
		Server_OnCalculatePlayerYawRotation(quatRotationToAdd);
}


void  APlayerPawn::Server_OnCalculatePlayerYawRotation_Implementation(FQuat quatRotationToAdd)
{
	AddActorLocalRotation(quatRotationToAdd, false, 0, ETeleportType::None);
}

void APlayerPawn::CalculateCameraPitchRotation(float DeltaTime)
{
	float pitchToAdd = _playerInput.RightAxistState.Y * _maxCameraSpeedRotation * DeltaTime;
	FRotator newRotation = _cameraSpringArm->GetRelativeRotation() + FRotator(pitchToAdd, 0, 0);
	newRotation.Pitch = UKismetMathLibrary::ClampAngle(newRotation.Pitch, -60.0f, 60.0f);
	_cameraSpringArm->SetRelativeRotation(newRotation);
}

void  APlayerPawn::CalculateVelocity()
{
	_currentSpeed = (UKismetMathLibrary::Abs(_playerInput.LeftAxistState.X) + UKismetMathLibrary::Abs(_playerInput.LeftAxistState.Y)) * _maxSpeed;
}

void  APlayerPawn::Server_OnSetAnimationVariables_Implementation(float directionX, float directionY)
{
	Multicast_OnSetAnimationVariables(directionX, directionY);
}

void APlayerPawn::Multicast_OnSetAnimationVariables_Implementation(float directionX, float directionY)
{
	if (GetAnimation() != nullptr && !IsLocallyControlled())
	{
		GetAnimation()->_directionX = directionX;
		GetAnimation()->_directionY = directionY;
	}
}

void  APlayerPawn::SetAnimationVariables()
{
	if (GetAnimation() != nullptr) {
		GetAnimation()->_directionX = _playerInput.LeftAxistState.X;
		GetAnimation()->_directionY = _playerInput.LeftAxistState.Y;

		if (!HasAuthority())
			Server_OnSetAnimationVariables(GetAnimation()->_directionX, GetAnimation()->_directionY);
		else
			Multicast_OnSetAnimationVariables(GetAnimation()->_directionX, GetAnimation()->_directionY);
	}
}

void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (!IsLocallyControlled())
		return;

	InputComponent->BindAxis("MoveX", this, &APlayerPawn::InputMoveX);
	InputComponent->BindAxis("MoveY", this, &APlayerPawn::InputMoveY);
	InputComponent->BindAxis("MoveCameraX", this, &APlayerPawn::InputMoveCameraX);
	InputComponent->BindAxis("MoveCameraY", this, &APlayerPawn::InputMoveCameraY);
	ConfigureInputForUI();
}

void APlayerPawn::ConfigureInputForGamePlay()
{
	if (!IsLocallyControlled())
		return;
	_playerInput.Enabled = true;
	InputComponent->ClearActionBindings();
	InputComponent->BindAction("Interaction", IE_Pressed, this, &APlayerPawn::Interact);
	InputComponent->BindAction("Quit", IE_Pressed, this, &APlayerPawn::ExitSession);
}

void APlayerPawn::ConfigureInputForUI()
{
	if (!IsLocallyControlled())
		return;
	_playerInput.Enabled = false;
	InputComponent->ClearActionBindings();
	if (GetPHUD())
	{
		InputComponent->BindAction("UIConfirm", IE_Pressed, GetPHUD(), &APlayerHUD::ButtonConfirmPressed);
		InputComponent->BindAction("UIStart", IE_Pressed, GetPHUD(), &APlayerHUD::ButtonStartPressed);
		InputComponent->BindAction("UIBack", IE_Pressed, GetPHUD(), &APlayerHUD::ButtonBackPressed);
		InputComponent->BindAction("UIUp", IE_Pressed, GetPHUD(), &APlayerHUD::ButtonUpPressed);
		InputComponent->BindAction("UIDown", IE_Pressed, GetPHUD(), &APlayerHUD::ButtonDownPressed);
		InputComponent->BindAction("UILeft", IE_Pressed, GetPHUD(), &APlayerHUD::ButtonLeftPressed);
		InputComponent->BindAction("UIRight", IE_Pressed, GetPHUD(), &APlayerHUD::ButtonRightPressed);		
	}
}


void APlayerPawn::SetCanInteractWith(AInteractableBase* interactable)
{
	if (IsLocallyControlled())
	{
		_interactableHandler = interactable;
		GetPlayerState()->GetPlayerController()->GetHUD<APlayerHUD>()->EnableInteractMsg();
	}
}

void APlayerPawn::SetCleanInteractable()
{
	if (IsLocallyControlled())
	{
		if (_interactableHandler) {
			AShowTextInteractable* _showTextInteractable = Cast<AShowTextInteractable>(_interactableHandler);
			if (_showTextInteractable)
				_showTextInteractable->Desinteract(this);
		}
		_interactableHandler = nullptr;
		GetPlayerState()->GetPlayerController()->GetHUD<APlayerHUD>()->DisableInteractMsg();
	}
}

void APlayerPawn::InputMoveX(float x)
{
	_playerInput.UpdateLeftAxisX(x);

}

void APlayerPawn::Interact()
{
	if (_interactableHandler && _playerInput.Enabled)
	{
		if (_interactableHandler->InteractOnlyInCLient)
			_interactableHandler->Interact(this);
		else
			Server_Interact(_interactableHandler);
	}
}

void APlayerPawn::Server_Interact_Implementation(AInteractableBase* interactable)
{
	interactable->Interact(this);
}

void APlayerPawn::InputMoveY(float y)
{
	_playerInput.UpdateLeftAxisY(y);
}

void APlayerPawn::InputMoveCameraX(float x)
{
	_playerInput.UpdateRightAxisX(x);
}

void APlayerPawn::InputMoveCameraY(float y)
{
	_playerInput.UpdateRightAxisY(y);
}


APState* APlayerPawn::GetPState()
{
	return  GetPlayerState<APState>();
}

APlayerHUD* APlayerPawn::GetPHUD()
{
	return UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD<APlayerHUD>();
}

void APlayerPawn::ExitSession()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, true);
}

UPlayerAnimInstance* APlayerPawn::GetAnimation()
{
	return Cast<UPlayerAnimInstance>(_mesh->GetAnimInstance());
}


int APlayerPawn::GetPlayerIndex()
{
	return _playerIndex;
}

int APlayerPawn::GetLocalPlayerIndex()
{
	return _localPlayerIndex;

}


int APlayerPawn::NexPlayerIndex = 0;

UFUNCTION(Server, Reliable)
void APlayerPawn::Server_SetPlayerIndex_Implementation()
{
	_playerIndex = NexPlayerIndex++;
}


void APlayerPawn::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APlayerPawn, _playerIndex);
}