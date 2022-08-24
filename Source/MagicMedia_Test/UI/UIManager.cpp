// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManager.h"

void UUIManager::Register(APlayerHUD* playerHUD)
{
	_HUDS.Push(playerHUD);
}

void UUIManager::Unregister(APlayerHUD* playerHUD)
{
	_HUDS.Remove(playerHUD);
}

void UUIManager::ChangeAllPlayersScreen(UIType uiType)
{
	for (APlayerHUD* hud : _HUDS)
	{
		hud->ChangeScreen(uiType);
	}
}

void UUIManager::PlayerTwoIsEnable()
{
	for (APlayerHUD* hud : _HUDS)
	{
		hud->PlayerTwoIsEnable();
	}
}

void UUIManager::UpdateAllSetUpWidget()
{
	for (APlayerHUD* hud : _HUDS)
	{
		hud->_setUpInstance->UpdateGeneralMessage();
	}
}


void UUIManager::StartGameplay()
{
	for (APlayerHUD* hud : _HUDS)
	{
		if (!hud)
			continue;
		hud->_currentUIinControll->DisableInputs();
		hud->ChangeScreen(UIType::GAMEPLAY);
	}
}