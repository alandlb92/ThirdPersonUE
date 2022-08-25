// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/InteractableManager.h"
#include "Interactables/ShowTextInteractable.h"
#include "Interactables/InteractableBase.h"

void UInteractableManager::Register(AInteractableBase* interactable)
{
	_interactables.Push(interactable);

	AShowTextInteractable* showTextInteractable = Cast<AShowTextInteractable>(interactable);
	if (showTextInteractable)
		showTextInteractable->OnPlayerInteract = OnShowTextInteract;
}

void UInteractableManager::Unregister(AInteractableBase* interactable)
{
	_interactables.Push(interactable);
}