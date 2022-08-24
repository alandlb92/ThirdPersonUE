// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PState.generated.h"

/**
 * 
 */
UCLASS()
class MAGICMEDIA_TEST_API APState : public APlayerState
{
	GENERATED_BODY()
	friend class UPlyerManager;

public:
	void BeginPlay() override;
	bool ready = false;
	FString name;

private:
	static int _nextId;
};
