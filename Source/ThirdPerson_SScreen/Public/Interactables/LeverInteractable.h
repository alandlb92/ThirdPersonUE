// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactables/InteractableBase.h"
#include "LeverInteractable.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSON_SSCREEN_API ALeverInteractable : public AInteractableBase
{
	GENERATED_BODY()

public:
	ALeverInteractable();
	UWorld* _word;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Interact(APlayerPawn* player) override;
	virtual void Desinteract(APlayerPawn* player) override;

	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* _sMeshLever;
	UPROPERTY(EditAnywhere)
	USceneComponent* _rotatorPivot;
	UPROPERTY(EditAnywhere)
	class URotatorComponent* _rotator;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* _meshToRotate;


	UFUNCTION(NetMulticast, Reliable)
	void Multicast_PlayAnimation();

	UFUNCTION()
	void OnAnimationEnd();
};
