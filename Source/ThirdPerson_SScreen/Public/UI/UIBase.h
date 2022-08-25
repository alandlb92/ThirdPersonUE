// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIBase.generated.h"


enum UIType
{
	START,
	SETUP,
	GAMEPLAY
};

struct BaseUiSetUp
{
public:
	std::function<void(UUIBase*)> _onEnableInputs;
	std::function<void()> _onDisableInputs;
	std::function<void(enum UIType)> _onChangeScreen;
};

UCLASS()
class THIRDPERSON_SSCREEN_API UUIBase : public UUserWidget
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
	virtual void ButtonStartPressed();
	virtual void ButtonUpPressed();
	virtual void ButtonDownPressed();
	virtual void ButtonLeftPressed();
	virtual void ButtonRightPressed();
	virtual void ButtonPPressed();

private:
	std::function<void(UUIBase*)> OnEnableInputs;
	std::function<void()> OnDisableInputs;
	std::function<void(UIType)> OnChangeScreen;
};
