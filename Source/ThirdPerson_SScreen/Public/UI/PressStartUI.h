// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UIBase.h"
#include "PressStartUI.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSON_SSCREEN_API UPressStartUI : public UUIBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void CallStartPressed();

	UFUNCTION(BlueprintCallable)
	void AnimationStartPressedFinished();

	void ButtonConfirmPressed() override;
	void ButtonStartPressed() override;
	
};
