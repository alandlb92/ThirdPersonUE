// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerPawn.h"
#include "GameFramework/GameModeBase.h"
#include "ThirdPerson_SScreenGameModeBase.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerRegistered, APlayerPawn*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerShowTextInteract, int, playerId, FString, text);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerHideTextIfShowing, int, playerId);

UCLASS()
class THIRDPERSON_SSCREEN_API AThirdPerson_SScreenGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
};
