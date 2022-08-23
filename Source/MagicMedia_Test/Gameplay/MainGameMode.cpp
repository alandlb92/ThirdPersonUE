// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "GameFramework/PlayerInput.h"
#include "GameFramework/HUD.h"
#include "Kismet/GameplayStatics.h"

void AMainGameMode::StartPlay()
{
	_playerManager = NewObject<UPlyerManager>();
	_UIManager = NewObject<UUIManager>();

	Super::StartPlay();
	GetWorld()->GetGameViewport()->SetDisableSplitscreenOverride(false);
}

UPlyerManager* AMainGameMode::GetPlayerManager()
{
	return _playerManager;
}

UUIManager* AMainGameMode::GetHUDManager()
{
	return _UIManager;
}