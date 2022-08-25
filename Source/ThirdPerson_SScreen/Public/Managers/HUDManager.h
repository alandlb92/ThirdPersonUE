// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UIBase.h"
#include "HUDManager.generated.h"

UCLASS()
class THIRDPERSON_SSCREEN_API UHUDManager : public UObject
{
	GENERATED_BODY()
	friend class AThirdPerson_SScreenGameModeBase;
public:
	void StartGameplay();

	void Register(class APlayerHUD* playerHUD);
	void Unregister(class APlayerHUD* playerHUD);
	void ChangeAllPlayersScreen(UIType uiType);
	void PlayerTwoIsEnable();
	void UpdateAllSetUpWidget();

	UFUNCTION()
	void ShowText(int playerId, FString text);

private:
	TArray<class APlayerHUD*> _HUDS;
};
