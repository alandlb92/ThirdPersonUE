// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ThirdPerson_SScreenGameModeBase.h"
#include "InteractableManager.generated.h"


UCLASS()
class THIRDPERSON_SSCREEN_API UInteractableManager : public UObject
{
	GENERATED_BODY()
	friend class AThirdPerson_SScreenGameModeBase;

public:
	void Register(class AInteractableBase* interactable);
	void Unregister(class AInteractableBase* interactable);
	FOnPlayerShowTextInteract OnShowTextInteract;
	FOnPlayerHideTextIfShowing OnHideTextIfShowing;

private:
	bool* gamePlayStarts;
	void StartGameplay();
	TArray<class AInteractableBase*> _interactables;
};
