// Fill out your copyright notice in the Description page of Project Settings.
#include "Managers/LevelManager.h"
#include "Managers/InteractableManager.h"
#include "Managers/PlayerManager.h"


void ALevelManager::PreInitializeComponents()
{
	Super::PreInitializeComponents();
	_interactableManager = NewObject<UInteractableManager>();
	_playerManager = NewObject<UPlayerManager>();
}


UInteractableManager* ALevelManager::GetInteractableManager()
{
	return _interactableManager;
}

UPlayerManager* ALevelManager::GetPlayerManager()
{
	return _playerManager;
}