// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/ShowTextInteractable.h"
#include "Player/PlayerPawn.h"


void AShowTextInteractable::BeginPlay()
{
	Super::BeginPlay();
}

void AShowTextInteractable::Interact(APlayerPawn* player)
{
	player->OnShowTextInteract.Broadcast(textToShow);
}

void AShowTextInteractable::Desinteract(APlayerPawn* player)
{
	player->OnHideTextInteract.Broadcast();
}