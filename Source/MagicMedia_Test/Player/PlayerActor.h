// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "PlayerAnimInstance.h"
#include "PlayerActor.generated.h"


struct FPlayerInput
{
public:
	FVector2D LeftAxistState;
	FVector2D RightAxistState;

	void Sanitize();
	void UpdateLeftAxisX(float x);
	void UpdateLeftAxisY(float y);
	void UpdateRightAxisX(float x);
	void UpdateRightAxisY(float y);

private:
	FVector2D _rawLeftAxis;
	FVector2D _rawRightAxis;
};

UCLASS()
class MAGICMEDIA_TEST_API APlayerActor : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void CalculatePlayerXYMovement(float DeltaTime);
	void CalculatePlayerYawRotation(float DeltaTime);
	void CalculateCameraPitchRotation(float DeltaTime);
	void SetAnimationVariables();
	void CalculateVelocity();
	void InputMoveX(float x);
	void InputMoveY(float y);
	void InputMoveCameraX(float x);
	void InputMoveCameraY(float y);

	
	UPlayerAnimInstance* _animation;
	FPlayerInput _playerInput;

	UPROPERTY(EditAnywhere)
	float _maxSpeed;

	UPROPERTY(EditAnywhere)
	float _maxPlayerSpeedRotation;
	UPROPERTY(EditAnywhere)
	float _maxCameraSpeedRotation;
	
	float _currentSpeed;

	UPROPERTY(EditAnywhere)
	USpringArmComponent* _cameraSpringArm;	

	UPROPERTY(EditAnywhere)
	UCameraComponent* _camera;
};
