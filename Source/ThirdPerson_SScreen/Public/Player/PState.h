// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PState.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSON_SSCREEN_API APState : public APlayerState
{
	GENERATED_BODY()

public:
	bool ready = false;
	FString name;
};
