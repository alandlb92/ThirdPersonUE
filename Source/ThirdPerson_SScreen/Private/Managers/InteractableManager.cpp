// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/InteractableManager.h"


UInteractableManager::UInteractableManager() : UObject()
{
	_container.Empty();
}

void UInteractableManager::Register(AInteractableBase* interactable)
{
	_container.Add(interactable);
}