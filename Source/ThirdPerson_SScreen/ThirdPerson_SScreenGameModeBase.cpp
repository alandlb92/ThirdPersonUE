// Copyright Epic Games, Inc. All Rights Reserved.


#include "ThirdPerson_SScreenGameModeBase.h"
#include "Managers/HUDManager.h"
#include "Managers/PlayerManager.h"
#include "Managers/InteractableManager.h"


void AThirdPerson_SScreenGameModeBase::StartPlay()
{
	GamePlayStarts = false;
	_playerManager = NewObject<UPlayerManager>();
	_HUDManager = NewObject<UHUDManager>();
	_interactableManager = NewObject<UInteractableManager>();

	_interactableManager->gamePlayStarts = &GamePlayStarts;
	_playerManager->ResetPlayersIds();
	_interactableManager->OnShowTextInteract.AddDynamic(_HUDManager, &UHUDManager::ShowText);
	_interactableManager->OnHideTextIfShowing.AddDynamic(_HUDManager, &UHUDManager::HideTextIfIsShowing);

	Super::StartPlay();
	GetWorld()->GetGameViewport()->SetDisableSplitscreenOverride(false);
}


void AThirdPerson_SScreenGameModeBase::StartGameplay()
{
	GamePlayStarts = true;
	_playerManager->StartGameplay();
	_HUDManager->StartGameplay();
	_interactableManager->StartGameplay();
}

UPlayerManager* AThirdPerson_SScreenGameModeBase::GetPlayerManager()
{
	return _playerManager;
}

UHUDManager* AThirdPerson_SScreenGameModeBase::GetHUDManager()
{
	return _HUDManager;
}

UInteractableManager* AThirdPerson_SScreenGameModeBase::GetInteractableManager()
{
	return _interactableManager;
}