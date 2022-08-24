// Fill out your copyright notice in the Description page of Project Settings.


#include "StartCameraComponent.h"
#include "../Player/PlayerActor.h"
#include "Kismet/GameplayStatics.h"
#include "../Gameplay/MainGameMode.h"

UStartCameraComponent::UStartCameraComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UStartCameraComponent::BeginPlay()
{
	Super::BeginPlay();
	Cast<AMainGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->GetPlayerManager()->OnPlayerRegistered.AddUObject(this, &UStartCameraComponent::OnPlayerRegistered);
}

void UStartCameraComponent::OnPlayerRegistered(APlayerActor* playerController)
{
	playerController->GetPlayerState()->GetPlayerController()->SetViewTarget(GetOwner());
}