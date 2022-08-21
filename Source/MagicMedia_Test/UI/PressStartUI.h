// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseUI.h"
#include "PressStartUI.generated.h"

/**
 * 
 */
UCLASS()
class MAGICMEDIA_TEST_API UPressStartUI : public UBaseUI
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintImplementableEvent)
	void CallStartPressed();

	UFUNCTION(BlueprintCallable)
	void AnimationStartPressedFinished();

	void ButtonConfirmPressed() override;

};
