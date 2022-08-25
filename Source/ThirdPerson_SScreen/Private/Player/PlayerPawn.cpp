// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerPawn.h"
#include "Interactables/InteractableBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Player/PlayerAnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "../ThirdPerson_SScreenGameModeBase.h"
#include "InWorldUI/PlayerLabelIWUI.h"
#include "GameFramework/PlayerState.h"
#include "Player/Pstate.h"
#include "Managers/PlayerManager.h"

void FPlayerInput::UpdateLeftAxisX(float x)
{
	_rawLeftAxis.X = x;	 
}

void FPlayerInput::UpdateLeftAxisY(float y)
{
	_rawLeftAxis.Y = y;
}

void FPlayerInput::UpdateRightAxisX(float x)
{
	_rawRightAxis.X = x;
}

void FPlayerInput::UpdateRightAxisY(float y)
{
	_rawRightAxis.Y = y;
}

void FPlayerInput::Sanitize()
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
	_maxPlayerSpeedRotation = 100.0f;
	_maxCameraSpeedRotation = 50.0f;

	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	_playerInput.Enabled = false;
	SetActorHiddenInGame(true);
	_animation = Cast<UPlayerAnimInstance>(_mesh->GetAnimInstance());
	_gameMode = Cast<AThirdPerson_SScreenGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	_gameMode->GetPlayerManager()->Register(this);
}

void APlayerPawn::StartGameplay()
{
	ConfigureInput();
	_labelWidgetInstance = Cast<UPlayerLabelIWUI>(_widget3D->GetWidget());
	GetPlayerState()->GetPlayerController()->SetViewTargetWithBlend(this, 1);
	_playerInput.Enabled = true;
	SetActorHiddenInGame(false);
	if (_labelWidgetInstance)
		_labelWidgetInstance->SetLabel(GetPState()->name);
}


void APlayerPawn::ConfigureInput()
{
	InputComponent->BindAxis("MoveX", this, &APlayerPawn::InputMoveX);
	InputComponent->BindAxis("MoveY", this, &APlayerPawn::InputMoveY);
	InputComponent->BindAxis("MoveCameraX", this, &APlayerPawn::InputMoveCameraX);
	InputComponent->BindAxis("MoveCameraY", this, &APlayerPawn::InputMoveCameraY);
	InputComponent->BindAction("Interaction", IE_Pressed, this, &APlayerPawn::Interact);
}

void APlayerPawn::Destroyed()
{
	Super::Destroyed();
	if (_gameMode && _gameMode->GetPlayerManager())
		_gameMode->GetPlayerManager()->Unregister(this);
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	if (GetLocalViewingPlayerController() && !camereSeted)
	{
		camereSeted = true;
		OnAdjustCameraOnStart.Broadcast(this);
	}

	Super::Tick(DeltaTime);
	_playerInput.Sanitize();
	CalculatePlayerXYMovement(DeltaTime);
	CalculatePlayerYawRotation(DeltaTime);
	CalculateCameraPitchRotation(DeltaTime);
	CalculateVelocity();
	SetAnimationVariables();
}

void  APlayerPawn::CalculatePlayerXYMovement(float DeltaTime)
{
	FVector2D movementX = _playerInput.LeftAxistState.X * _maxSpeed * FVector2D(GetActorRightVector());
	FVector2D movementY = _playerInput.LeftAxistState.Y * _maxSpeed * FVector2D(GetActorForwardVector());
	FVector movement = FVector(movementX + movementY, 0) * DeltaTime;

	FVector newPosition = (GetActorLocation()) + movement;
	SetActorLocation(newPosition);
}


void APlayerPawn::CalculatePlayerYawRotation(float DeltaTime)
{
	float yawToAdd = _playerInput.RightAxistState.X * _maxPlayerSpeedRotation * DeltaTime;
	FQuat quatRotation = FQuat(FRotator(0, yawToAdd, 0));
	AddActorLocalRotation(quatRotation, false, 0, ETeleportType::None);
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

void  APlayerPawn::SetAnimationVariables()
{
	if (_animation != nullptr) {
		_animation->_directionY = _playerInput.LeftAxistState.Y;
		_animation->_directionX = _playerInput.LeftAxistState.X;
	}
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerPawn::SetCanInteractWith(AInteractableBase* interactable)
{
	UE_LOG(LogTemp, Warning, TEXT("SetCanInteractWith %s"), interactable ? TEXT("True") : TEXT("False"));
	_interactableHandler = interactable;
}

void APlayerPawn::SetCleanInteractable()
{
	_interactableHandler = nullptr;
}

void APlayerPawn::InputMoveX(float x)
{
	_playerInput.UpdateLeftAxisX(x);
}

void APlayerPawn::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("Interact"));
	if (_interactableHandler && _playerInput.Enabled)
		_interactableHandler->Interact(GetPState()->GetPlayerId());
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


class APState* APlayerPawn::GetPState()
{
	return  GetPlayerState<APState>();
}