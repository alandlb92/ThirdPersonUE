// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/PlayerManager.h"
#include "Player/PlayerPawn.h"


UPlayerManager::UPlayerManager() : UObject()
{
	_container.Empty();
}

void UPlayerManager::Register(APlayerPawn* player)
{
	if (!_container.Contains(player))
	{
		_container.Add(player);
		if (player->IsLocallyControlled()) {
			player->_localPlayerIndex = nextPlayerIndex++;
		}
		OnLocalPlayerRegistered.Broadcast(player);
	}
}

void  UPlayerManager::GetLocalPlayers(TArray<APlayerPawn*>& localPlayers)
{
	for (APlayerPawn* player : _container)
	{
		if (player->IsLocallyControlled())
			localPlayers.Add(player);
	}
}