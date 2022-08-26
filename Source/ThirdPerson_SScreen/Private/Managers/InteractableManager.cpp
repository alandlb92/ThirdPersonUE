// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/InteractableManager.h"
#include "Interactables/ShowTextInteractable.h"
#include "Interactables/InteractableBase.h"

void UInteractableManager::Register(AInteractableBase* interactable)
{
	if (interactable) {
		_interactables.Push(interactable);

		AShowTextInteractable* showTextInteractable = Cast<AShowTextInteractable>(interactable);
		if (showTextInteractable) {
			showTextInteractable->OnPlayerInteract = OnShowTextInteract;
			showTextInteractable->OnPlayerDesinteract = OnHideTextIfShowing;
		}

		if (!*gamePlayStarts)
			interactable->DisableUI();
	}
}

void UInteractableManager::Unregister(AInteractableBase* interactable)
{
	if (interactable)
		_interactables.Push(interactable);
}

void UInteractableManager::StartGameplay()
{
	for (AInteractableBase* it : _interactables)
	{
		it->EnableUI();
	}
}