// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../ThirdPerson_SScreenGameModeBase.h"
#include "PlayerManager.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSON_SSCREEN_API UPlayerManager : public UObject
{
	GENERATED_BODY()
public:
	FOnPlayerRegistered OnLocalPlayerRegistered;

	UPlayerManager();
	void Register(class APlayerPawn* interactable);
	void GetLocalPlayers(TArray<APlayerPawn*>& localPlayers);
private:
	UPROPERTY()
	TArray<class APlayerPawn*> _container;
	int nextPlayerIndex;
	
};
