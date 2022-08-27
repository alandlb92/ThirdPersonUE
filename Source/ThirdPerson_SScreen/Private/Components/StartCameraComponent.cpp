// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StartCameraComponent.h"
#include "Player/PlayerPawn.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerState.h"

// Sets default values for this component's properties
UStartCameraComponent::UStartCameraComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UStartCameraComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UStartCameraComponent::OnPlayerRegistered(APlayerPawn* player)
{
	player->GetPlayerState()->GetPlayerController()->SetViewTarget(GetOwner());
}