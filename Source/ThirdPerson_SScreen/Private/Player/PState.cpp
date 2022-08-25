// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PState.h"

int APState::_nextId = 0;


void APState::BeginPlay()
{
	Super::BeginPlay();
	SetPlayerId(_nextId++);
	UE_LOG(LogTemp, Warning, TEXT("Setup new player id: %i"), PlayerId);
}