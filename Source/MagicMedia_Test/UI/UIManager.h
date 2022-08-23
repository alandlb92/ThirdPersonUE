// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerHUD.h"
#include "UObject/NoExportTypes.h"
#include <functional>
#include "UIManager.generated.h"


UCLASS()
class MAGICMEDIA_TEST_API UUIManager : public UObject
{
	GENERATED_BODY()
	friend class AMainGameMode;
public:
	void Register(APlayerHUD* playerHUD);
	void Unregister(APlayerHUD* playerHUD);
	void ChangeAllPlayersScreen(UIType uiType);
	void PlayerTwoIsEnable();

private:
	TArray<APlayerHUD*> _HUDS;
};
