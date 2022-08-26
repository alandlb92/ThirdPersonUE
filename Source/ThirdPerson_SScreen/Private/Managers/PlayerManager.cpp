// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/PlayerManager.h"
#include "Player/PState.h"
#include "Player/PlayerPawn.h"
#include "Kismet/GameplayStatics.h"

void FPlayerContainer::AddPlayer(APlayerPawn* player)
{
	_players.Push(player);
}

void FPlayerContainer::RemovePlayer(APlayerPawn* player)
{
	_players.Remove(player);
}

int FPlayerContainer::GetCount()
{
	return _players.Num();
}


void UPlayerManager::ResetPlayersIds()
{
	APState::_nextId = 0;
}

void UPlayerManager::Register(APlayerPawn* player)
{
	if (player)
	{
		_playerContainer.AddPlayer(player);
		//player->OnAdjustCameraOnStart = &OnPlayerRegistered;
	}
}

void UPlayerManager::Unregister(APlayerPawn* player)
{
	if (player)
		_playerContainer.RemovePlayer(player);
}

void UPlayerManager::CreatePlayer2(UWorld* world)
{
	APlayerController* player2Cotroller = UGameplayStatics::CreatePlayer(world);
}

APlayerPawn* UPlayerManager::GetPlayerByInputIndex(int index)
{
	for (APlayerPawn* player : _playerContainer._players)
	{
		if (player->GetPState()->PlayerId == index)
			return player;
	}
	return nullptr;
}

bool UPlayerManager::AllPlayerIsReady()
{
	if (_playerContainer.GetCount() == 0)
		return false;

	bool result = true;
	for (APlayerPawn* player : _playerContainer._players)
	{
		if (!player)
			continue;

		APState* pState = player->GetPState();
		if (pState)
			result &= pState->ready;
	}
	return result;
}

bool UPlayerManager::PlayerOneIsReady()
{
	APlayerPawn* player = GetPlayerByInputIndex(0);
	if (player)
		return player->GetPState()->ready;
	else return false;
}

bool UPlayerManager::PlayerTwoIsReady()
{
	APlayerPawn* player = GetPlayerByInputIndex(1);

	if (player)
		return player->GetPState()->ready;
	else return false;
}

bool UPlayerManager::PlayerTwoIsJoined()
{
	return _playerContainer.GetCount() > 1;
}


void UPlayerManager::StartGameplay()
{
	for (APlayerPawn* player : _playerContainer._players)
	{
		if (!player)
			continue;
		player->StartGameplay();
	}
}
