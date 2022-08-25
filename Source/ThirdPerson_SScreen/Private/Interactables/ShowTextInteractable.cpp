// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/ShowTextInteractable.h"


void AShowTextInteractable::BeginPlay()
{
	Super::BeginPlay();
}

void AShowTextInteractable::Interact(int playerId)
{

	Super::Interact(playerId);
	UE_LOG(LogTemp, Warning, TEXT("AShowTextInteratable Interact"));
	OnPlayerInteract.Broadcast(playerId, textToShow);
}