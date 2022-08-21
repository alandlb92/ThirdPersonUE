// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MAGICMEDIA_TEST_API ATPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	void BeginPlay() override;
	
};
