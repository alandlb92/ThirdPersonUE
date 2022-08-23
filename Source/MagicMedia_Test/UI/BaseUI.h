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

	virtual void ButtonBackPressed_Player1();
	virtual void ButtonConfirmPressed_Player1();
	virtual void ButtonUpPressed_Player1();
	virtual void ButtonDownPressed_Player1();
	virtual void ButtonLeftPressed_Player1();
	virtual void ButtonRightPressed_Player1();

	virtual void ButtonBackPressed_Player2();
	virtual void ButtonConfirmPressed_Player2();
	virtual void ButtonUpPressed_Player2();
	virtual void ButtonDownPressed_Player2();
	virtual void ButtonLeftPressed_Player2();
	virtual void ButtonRightPressed_Player2();

private:
	std::function<void(UBaseUI*)> OnEnableInputs;
	std::function<void()> OnDisableInputs;
	std::function<void(UIType)> OnChangeScreen;
};
