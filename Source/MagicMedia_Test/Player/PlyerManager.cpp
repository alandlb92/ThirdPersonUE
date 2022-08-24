// Fill out your copyright notice in the Description page of Project Settings.


#include "PlyerManager.h"
#include "PState.h"
#include "Kismet/GameplayStatics.h"


void UPlyerManager::ResetPlayersIds()
{
	APState::_nextId = 0;
}

void UPlyerManager::Register(APlayerActor* player)
{
	_players.Push(player);
	player->OnAdjustCameraOnStart = OnPlayerRegistered;
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
	if (_players.Num() == 0)
		return false;

	bool result = true;
	for (APlayerActor* player : _players)
	{
		if (!player)
			continue;

		APState* pState = player->GetController()->GetPlayerState<APState>();
		if (pState)
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
	return _players.Num() > 1;
}


void UPlyerManager::StartGameplay()
{
	for (APlayerActor* player : _players)
	{
		if (!player)
			continue;
		player->StartGameplay();
	}
}