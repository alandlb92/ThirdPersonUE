// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/ShowTextInteractable.h"


void AShowTextInteractable::BeginPlay()
{
	Super::BeginPlay();
}

void AShowTextInteractable::Interact(int playerId)
{
	OnPlayerInteract.Broadcast(playerId, textToShow);
}

void AShowTextInteractable::Desinteract(int playerId)
{
	OnPlayerDesinteract.Broadcast(playerId);
}