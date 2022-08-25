// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactables/InteractableBase.h"
#include "../ThirdPerson_SScreenGameModeBase.h"
#include "ShowTextInteractable.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSON_SSCREEN_API AShowTextInteractable : public AInteractableBase
{
	GENERATED_BODY()
	friend class UInteractableManager;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString textToShow;
	virtual void BeginPlay() override;
	virtual void Interact(int playerId) override;
	virtual void Desinteract(int playerId) override;

private:
	FOnPlayerShowTextInteract OnPlayerInteract;
	FOnPlayerHideTextIfShowing OnPlayerDesinteract;
	
};
