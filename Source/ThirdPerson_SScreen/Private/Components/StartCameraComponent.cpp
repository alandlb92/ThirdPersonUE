// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StartCameraComponent.h"
#include "Player/PlayerPawn.h"
#include "Managers/PlayerManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerState.h"
#include "../ThirdPerson_SScreenGameModeBase.h"

// Sets default values for this component's properties
UStartCameraComponent::UStartCameraComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UStartCameraComponent::BeginPlay()
{
	Super::BeginPlay();
	Cast<AThirdPerson_SScreenGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GetPlayerManager()->OnPlayerRegistered.AddUObject(this, &UStartCameraComponent::OnPlayerRegistered);

}

void UStartCameraComponent::OnPlayerRegistered(APlayerPawn* player)
{
	player->GetPlayerState()->GetPlayerController()->SetViewTarget(GetOwner());
}