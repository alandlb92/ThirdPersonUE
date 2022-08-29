// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InteractableManager.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSON_SSCREEN_API UInteractableManager : public UObject
{
	GENERATED_BODY()
public:
	UInteractableManager();
	void Register(class AInteractableBase* interactable);
private:
	UPROPERTY()
	TArray<AInteractableBase*> _container;
};
