// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ThirdPerson_SScreenGameModeBase.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerRegistered, class APlayerPawn*, player);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerShowTextInteract, FString, text);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerHideTextIfShowing);

UCLASS()
class THIRDPERSON_SSCREEN_API AThirdPerson_SScreenGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
};
