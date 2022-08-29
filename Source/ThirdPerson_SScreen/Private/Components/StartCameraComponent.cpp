// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StartCameraComponent.h"
#include "Player/PlayerPawn.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerState.h"
#include "Managers/PlayerManager.h"
#include "Managers/LevelManager.h"

// Sets default values for this component's properties
UStartCameraComponent::UStartCameraComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}


void UStartCameraComponent::BeginPlay()
{
	Super::BeginPlay();
	Cast<ALevelManager>(GetComponentLevel()->GetLevelScriptActor())
		->GetPlayerManager()->OnLocalPlayerRegistered.AddDynamic(this, &UStartCameraComponent::OnLocalPlayerRegistered);
}

void UStartCameraComponent::OnLocalPlayerRegistered(APlayerPawn* player)
{
	UGameplayStatics::GetPlayerController(player, player->GetLocalPlayerIndex())->SetViewTarget(GetOwner());
}