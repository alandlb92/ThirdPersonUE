// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StartCameraComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIRDPERSON_SSCREEN_API UStartCameraComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStartCameraComponent();

protected:
	virtual void BeginPlay() override;

private:
	void OnPlayerRegistered(class APlayerPawn* player);

		
};