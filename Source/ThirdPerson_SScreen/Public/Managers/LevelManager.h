// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "LevelManager.generated.h"

/**
 *
 */
UCLASS()
class THIRDPERSON_SSCREEN_API ALevelManager : public ALevelScriptActor
{
	GENERATED_BODY()
public:
	virtual void PreInitializeComponents() override;
	class UInteractableManager* GetInteractableManager();
	class UPlayerManager* GetPlayerManager();

private:
	UPROPERTY()
	class UInteractableManager* _interactableManager;
	UPROPERTY()
	class UPlayerManager* _playerManager;
};
