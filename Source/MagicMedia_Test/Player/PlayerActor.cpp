// Fill out your copyright notice in the Description page of Project Settings.
#include "PlayerActor.h"
#include "PState.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "../Gameplay/MainGameMode.h"

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
APlayerActor::APlayerActor()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
void APlayerActor::BeginPlay()
{
	Super::BeginPlay();
	_playerInput.Enabled = false;
	SetActorHiddenInGame(true);
	_animation = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	_gameMode = Cast<AMainGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	_gameMode->GetPlayerManager()->Register(this);
	UE_LOG(LogTemp, Warning, TEXT("BeginPlayer"));
}

void APlayerActor::StartGameplay()
{
	GetPlayerState()->GetPlayerController()->SetViewTargetWithBlend(this, 1);
	_playerInput.Enabled = true;
	SetActorHiddenInGame(false);
}

void APlayerActor::Destroyed()
{
	Super::Destroyed();
	if (_gameMode && _gameMode->GetPlayerManager())
		_gameMode->GetPlayerManager()->Unregister(this);
}

// Called every frame
void APlayerActor::Tick(float DeltaTime)
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

void  APlayerActor::CalculatePlayerXYMovement(float DeltaTime)
{
	FVector2D movementX = _playerInput.LeftAxistState.X * _maxSpeed * FVector2D(GetActorRightVector());
	FVector2D movementY = _playerInput.LeftAxistState.Y * _maxSpeed * FVector2D(GetActorForwardVector());
	FVector movement = FVector(movementX + movementY, 0) * DeltaTime;

	FVector newPosition = (GetActorLocation()) + movement;
	SetActorLocation(newPosition);
}


void APlayerActor::CalculatePlayerYawRotation(float DeltaTime)
{
	float yawToAdd = _playerInput.RightAxistState.X * _maxPlayerSpeedRotation * DeltaTime;
	FQuat quatRotation = FQuat(FRotator(0, yawToAdd, 0));
	AddActorLocalRotation(quatRotation, false, 0, ETeleportType::None);
}


void APlayerActor::CalculateCameraPitchRotation(float DeltaTime)
{
	float pitchToAdd = _playerInput.RightAxistState.Y * _maxCameraSpeedRotation * DeltaTime;
	FRotator newRotation = _cameraSpringArm->GetRelativeRotation() + FRotator(pitchToAdd, 0, 0);
	newRotation.Pitch = UKismetMathLibrary::ClampAngle(newRotation.Pitch, -60.0f, 60.0f);
	_cameraSpringArm->SetRelativeRotation(newRotation);
}

void  APlayerActor::CalculateVelocity()
{
	_currentSpeed = (UKismetMathLibrary::Abs(_playerInput.LeftAxistState.X) + UKismetMathLibrary::Abs(_playerInput.LeftAxistState.Y)) * _maxSpeed;
}

void  APlayerActor::SetAnimationVariables()
{
	if (_animation != nullptr) {
		_animation->_directionY = _playerInput.LeftAxistState.Y;
		_animation->_directionX = _playerInput.LeftAxistState.X;
	}
}

// Called to bind functionality to input
void APlayerActor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("MoveX", this, &APlayerActor::InputMoveX);
	InputComponent->BindAxis("MoveY", this, &APlayerActor::InputMoveY);
	InputComponent->BindAxis("MoveCameraX", this, &APlayerActor::InputMoveCameraX);
	InputComponent->BindAxis("MoveCameraY", this, &APlayerActor::InputMoveCameraY);
}

void APlayerActor::InputMoveX(float x)
{
	_playerInput.UpdateLeftAxisX(x);
}

void APlayerActor::InputMoveY(float y)
{
	_playerInput.UpdateLeftAxisY(y);
}

void APlayerActor::InputMoveCameraX(float x)
{
	_playerInput.UpdateRightAxisX(x);
}

void APlayerActor::InputMoveCameraY(float y)
{
	_playerInput.UpdateRightAxisY(y);
}


class APState* APlayerActor::GetPState()
{
	return  GetPlayerState<APState>();
}