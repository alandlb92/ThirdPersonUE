// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "GameFramework/PlayerInput.h"
#include "GameFramework/HUD.h"

void AMainGameMode::StartPlay()
{
	Super::StartPlay();
	APlayerController* player2Cotroller = UGameplayStatics::CreatePlayer(GetWorld());
	GetWorld()->GetGameViewport()->SetDisableSplitscreenOverride(true);
}