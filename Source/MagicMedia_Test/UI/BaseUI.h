// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <functional>
#include "BaseUI.generated.h"

struct BaseUiSetUp
{
public:
	std::function<void(UBaseUI*)> _onEnableInputs;
	std::function<void()> _onDisableInputs;
	std::function<void(enum UIType)> _onChangeScreen;
};

/**
 * 
 */
UCLASS()
class MAGICMEDIA_TEST_API UBaseUI : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetUp(BaseUiSetUp baseUiSetup);
	void Open();
	void Close();

	UFUNCTION(BlueprintImplementableEvent)
	void CallOpenAnimation();

	UFUNCTION(BlueprintImplementableEvent)
	void CallCloseAnimation();

	UFUNCTION(BlueprintCallable, Category = "Base UI")
	void EnableInputs();

	UFUNCTION(BlueprintCallable, Category = "Base UI")
	void DisableInputs();

	UFUNCTION(BlueprintCallable, Category = "Base UI")
	void CloseAnimationFinished();

	void ChangeScreen(UIType screenType);

	virtual void ButtonBackPressed();
	virtual void ButtonConfirmPressed();
	virtual void ButtonUpPressed();
	virtual void ButtonDownPressed();
	virtual void ButtonLeftPressed();
	virtual void ButtonRightPressed();

private:
	std::function<void(UBaseUI*)> OnEnableInputs;
	std::function<void()> OnDisableInputs;
	std::function<void(UIType)> OnChangeScreen;
};
