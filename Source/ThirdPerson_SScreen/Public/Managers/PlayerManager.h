// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ThirdPerson_SScreenGameModeBase.h"
#include "UObject/NoExportTypes.h"
#include "PlayerManager.generated.h"

USTRUCT()
struct THIRDPERSON_SSCREEN_API FPlayerContainer
{
	GENERATED_USTRUCT_BODY()

	void AddPlayer(APlayerPawn* player);
	void RemovePlayer(APlayerPawn* player);
	int GetCount();
	// An array which stores the picked up items.
	UPROPERTY()
	TArray<APlayerPawn*> _players;
};

UCLASS()
class THIRDPERSON_SSCREEN_API UPlayerManager : public UObject
{
	GENERATED_BODY()
	friend class ALevelManager;

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
	int GetPlayerCount() { return _playerContainer.GetCount(); }
	void CreatePlayer2(UWorld* world);

private:
	UPROPERTY()
	FPlayerContainer _playerContainer;
	void ResetPlayersIds();
};
