// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ThirdPerson_SScreenGameModeBase.h"
#include "UObject/NoExportTypes.h"
#include "PlayerManager.generated.h"

UCLASS()
class THIRDPERSON_SSCREEN_API UPlayerManager : public UObject
{
	GENERATED_BODY()
	friend class AThirdPerson_SScreenGameModeBase;

public:
	FOnPlayerRegistered OnPlayerRegistered;

	void StartGameplay();
	class APlayerPawn* GetPlayerByInputIndex(int index);
	bool AllPlayerIsReady();
	bool PlayerOneIsReady();
	bool PlayerTwoIsReady();
	bool PlayerTwoIsJoined();
	void Register(class APlayerPawn* player);
	void Unregister(class APlayerPawn* player);
	int GetPlayerCount() { return _players.Num(); }
	void CreatePlayer2(UWorld* world);

private:
	TArray<class APlayerPawn*> _players;
	void ResetPlayersIds();
};
