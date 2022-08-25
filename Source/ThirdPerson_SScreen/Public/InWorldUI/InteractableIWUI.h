// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "InteractableIWUI.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSON_SSCREEN_API UInteractableIWUI : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* _arrowImage;	
};
