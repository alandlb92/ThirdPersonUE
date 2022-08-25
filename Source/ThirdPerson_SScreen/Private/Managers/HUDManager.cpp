// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/HUDManager.h"
#include "Player/PlayerHUD.h"

void UHUDManager::Register(APlayerHUD* playerHUD)
{
	_HUDS.Push(playerHUD);
}

void UHUDManager::Unregister(APlayerHUD* playerHUD)
{
	_HUDS.Remove(playerHUD);
}

void UHUDManager::ChangeAllPlayersScreen(UIType uiType)
{
	for (APlayerHUD* hud : _HUDS)
	{
		hud->ChangeScreen(uiType);
	}
}

void UHUDManager::PlayerTwoIsEnable()
{
	for (APlayerHUD* hud : _HUDS)
	{
		hud->PlayerTwoIsEnable();
	}
}

APlayerHUD* UHUDManager::GetHudFromPlayer(int id)
{
	for (APlayerHUD* hud : _HUDS)
	{
		if (hud->PlayerOwner->PlayerState->GetPlayerId() == id)
			return hud;
	}

	return nullptr;
}

void UHUDManager::UpdateAllSetUpWidget()
{
	for (APlayerHUD* hud : _HUDS)
	{
		hud->_setUpInstance->UpdateGeneralMessage();
	}
}


void UHUDManager::StartGameplay()
{
	for (APlayerHUD* hud : _HUDS)
	{
		if (!hud)
			continue;

		hud->_currentUIinControll->DisableInputs();
		hud->ChangeScreen(UIType::GAMEPLAY);
		hud->ClearAllActions();
	}
}


void UHUDManager::ShowText(int playerId, FString text)
{
	APlayerHUD* hud = GetHudFromPlayer(playerId);
	if (hud && hud->IsShowingMessage)
		hud->HideText();
	else if (hud)
		hud->ShowText(text);
}

void UHUDManager::HideTextIfIsShowing(int playerId)
{

	APlayerHUD* hud = GetHudFromPlayer(playerId);
	if (hud && hud->IsShowingMessage)
		hud->HideText();
}