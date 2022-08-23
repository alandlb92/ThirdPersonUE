// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "MainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MAGICMEDIA_TEST_API AMainGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	void StartPlay() override;
};
