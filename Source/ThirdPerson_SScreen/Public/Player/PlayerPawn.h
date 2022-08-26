// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

USTRUCT()
struct THIRDPERSON_SSCREEN_API FPlayerPawnInput
{
	GENERATED_USTRUCT_BODY()
public:
	bool Enabled = true;
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

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerBegin, APlayerPawn*)

UCLASS()
class THIRDPERSON_SSCREEN_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	APlayerPawn();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	class APState* GetPState();
	void SetCanInteractWith(class AInteractableBase* interactable);
	void SetCleanInteractable();
	UFUNCTION(Server, Reliable)
	void StartGameplay();

private:

	class AInteractableBase* _interactableHandler;
	class UPlayerLabelIWUI* _labelWidgetInstance;

	void ConfigureInput();

	bool camereSeted;

	FOnPlayerBegin* OnAdjustCameraOnStart;

	void CalculatePlayerXYMovement(float DeltaTime);
	void CalculatePlayerYawRotation(float DeltaTime);
	void CalculateCameraPitchRotation(float DeltaTime);
	void SetAnimationVariables();
	void CalculateVelocity();
	void InputMoveX(float x);
	void InputMoveY(float y);
	void InputMoveCameraX(float x);
	void InputMoveCameraY(float y);
	void Interact();
	void ExitSession();

	class UPlayerAnimInstance* _animation;
	FPlayerPawnInput _playerInput;

	UPROPERTY(EditAnywhere)
	float _maxSpeed;

	UPROPERTY(EditAnywhere)
	float _maxPlayerSpeedRotation;
	UPROPERTY(EditAnywhere)
	float _maxCameraSpeedRotation;

	float _currentSpeed;

	UPROPERTY(EditAnywhere)
	class UCapsuleComponent* _collider;

	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* _mesh;

	UPROPERTY(EditAnywhere)
	class UWidgetComponent* _widget3D;

	UPROPERTY(EditAnywhere)
	class USpringArmComponent* _cameraSpringArm;

	UPROPERTY(EditAnywhere)
		class UCameraComponent* _camera;

	UPROPERTY(ReplicatedUsing=OnRep_Hidden)
	bool _isHidden;

	UFUNCTION()
	void OnRep_Hidden();

	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

};
