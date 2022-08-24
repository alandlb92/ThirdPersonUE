// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "GameFramework/PlayerInput.h"
#include "GameFramework/HUD.h"
#include "Kismet/GameplayStatics.h"

void AMainGameMode::StartPlay()
{
	_playerManager = NewObject<UPlyerManager>();
	_UIManager = NewObject<UUIManager>();

	_playerManager->ResetPlayersIds();

	Super::StartPlay();
	GetWorld()->GetGameViewport()->SetDisableSplitscreenOverride(false);
}


void AMainGameMode::StartGameplay()
{
	_playerManager->StartGameplay();
	_UIManager->StartGameplay();
}

UPlyerManager* AMainGameMode::GetPlayerManager()
{
	return _playerManager;
}

UUIManager* AMainGameMode::GetHUDManager()
{
	return _UIManager;
}