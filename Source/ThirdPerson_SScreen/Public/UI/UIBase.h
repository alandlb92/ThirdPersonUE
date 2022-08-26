// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIBase.generated.h"

UENUM()
enum class UIType : uint8
{
	START,
	SETUP,
	GAMEPLAY
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDisableInputs);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnableInputs, UUIBase*, ui);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeScreen, UIType, uiType);

UCLASS()
class THIRDPERSON_SSCREEN_API UUIBase : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void SetUp();
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


	FOnEnableInputs OnEnableInputs;
	FOnDisableInputs OnDisableInputs;
	FOnChangeScreen OnChangeScreen;
};
