// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "CoreMinimal.h"
#include "PlayerActor.h"
#include "UObject/NoExportTypes.h"
#include "PlyerManager.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerRegistered, APlayerActor*)

UCLASS()
class MAGICMEDIA_TEST_API UPlyerManager : public UObject
{
	GENERATED_BODY()
	friend class AMainGameMode;

public:
	FOnPlayerRegistered OnPlayerRegistered;

	void StartGameplay();
	APlayerActor* GetPlayerByInputIndex(int index);
	bool AllPlayerIsReady();
	bool PlayerOneIsReady();
	bool PlayerTwoIsReady();
	bool PlayerTwoIsJoined();
	void Register(APlayerActor* player);
	void Unregister(APlayerActor* player);
	int GetPlayerCount() { return _players.Num(); }
	void CreatePlayer2(UWorld* world);	

private:
	void ResetPlayersIds();
	TArray<APlayerActor*> _players;
};
