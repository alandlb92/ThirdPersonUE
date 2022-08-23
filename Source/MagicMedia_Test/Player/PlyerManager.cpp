// Fill out your copyright notice in the Description page of Project Settings.


#include "PlyerManager.h"
#include "PState.h"
#include "Kismet/GameplayStatics.h"

void UPlyerManager::Register(APlayerActor* player)
{
	_players.Push(player);
}

void UPlyerManager::Unregister(APlayerActor* player)
{
	_players.Remove(player);
}

void UPlyerManager::CreatePlayer2(UWorld* world)
{
	APlayerController* player2Cotroller = UGameplayStatics::CreatePlayer(world);
}

APlayerActor* UPlyerManager::GetPlayerByInputIndex(int index)
{
	for (APlayerActor* player : _players)
	{
		if (player->GetPState()->PlayerId == index)
			return player;
	}
	return nullptr;
}

bool UPlyerManager::AllPlayerIsReady()
{
	bool result = true;
	for (APlayerActor* player : _players)
	{
		APState* pState = player->GetController()->GetPlayerState<APState>();
		if (pState->joined)
			result &= pState->ready;
	}
	return result;
}

bool UPlyerManager::PlayerOneIsReady()
{
	APlayerActor* player = GetPlayerByInputIndex(0);
	if (player)
		return player->GetPState()->ready;
	else return false;
}

bool UPlyerManager::PlayerTwoIsReady()
{
	APlayerActor* player = GetPlayerByInputIndex(1);

	if (player)
		return player->GetPState()->ready;
	else return false;
}

bool UPlyerManager::PlayerTwoIsJoined()
{
	APlayerActor* player = GetPlayerByInputIndex(1);
	if (player)
		return player->GetPState()->joined;
	else return false;
}