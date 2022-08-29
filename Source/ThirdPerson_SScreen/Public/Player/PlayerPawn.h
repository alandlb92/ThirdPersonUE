// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "../ThirdPerson_SScreenGameModeBase.h"
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
	friend class UPlayerManager;
public:
	APlayerPawn();

protected:
	virtual void BeginPlay() override;

public:
	FOnPlayerShowTextInteract OnShowTextInteract;
	FOnPlayerHideTextIfShowing OnHideTextInteract;


	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;
	
	class APState* GetPState();
	

	void SetCanInteractWith(class AInteractableBase* interactable);
	void SetCleanInteractable();


	UFUNCTION(Server, Reliable)
	void Server_OnStartGameplay(const FString& name);
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_OnStartGameplay(const FString& name);
	void StartGameplay();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetComponent* _widget3D;


	int GetPlayerIndex();
	int GetLocalPlayerIndex();

private:
	UPROPERTY(Replicated)
	int _playerIndex;
	int _localPlayerIndex;
	static int NexPlayerIndex;
	UFUNCTION(Server, Reliable)
	void Server_SetPlayerIndex();

	class AInteractableBase* _interactableHandler;
	class UPlayerLabelIWUI* _labelWidgetInstance;

	void ConfigureInputForGamePlay();
	void ConfigureInputForUI();

	//TODO
	FOnPlayerBegin* OnAdjustCameraOnStart;

	UFUNCTION(Server, Reliable)
	void Server_OnSetAnimationVariables(float directionX, float directionY);
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_OnSetAnimationVariables(float directionX, float directionY);
	void SetAnimationVariables();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_OnCalculatePlayerXYMovement(FVector newPosition);
	void CalculatePlayerXYMovement(float DeltaTime);

	UFUNCTION(Server, Reliable)
	void Server_OnCalculatePlayerYawRotation(FQuat quatRotationToAdd);
	void CalculatePlayerYawRotation(float DeltaTime);

	void CalculateCameraPitchRotation(float DeltaTime);
	void CalculateVelocity();
	void InputMoveX(float x);
	void InputMoveY(float y);
	void InputMoveCameraX(float x);
	void InputMoveCameraY(float y);
	void Interact();
	void ExitSession();

	class UPlayerAnimInstance* GetAnimation();
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
	class USpringArmComponent* _cameraSpringArm;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* _camera;


	class APlayerHUD* GetPHUD(); 
};
