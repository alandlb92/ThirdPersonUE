// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerPawn.h"
#include "GameFramework/GameModeBase.h"
#include "ThirdPerson_SScreenGameModeBase.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerRegistered, APlayerPawn*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerShowTextInteract, int, playerId, FString, text);

UCLASS()
class THIRDPERSON_SSCREEN_API AThirdPerson_SScreenGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	void StartPlay() override;
	void StartGameplay();
	class UPlayerManager* GetPlayerManager();
	class UHUDManager* GetHUDManager();
	class UInteractableManager* GetInteractableManager();

private:
	UPlayerManager* _playerManager;
	UHUDManager* _HUDManager;
	UInteractableManager* _interactableManager;
	
};
