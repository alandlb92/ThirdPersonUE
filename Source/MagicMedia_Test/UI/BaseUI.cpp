// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseUI.h"
#include "UIManager.h"

void UBaseUI::SetUp(BaseUiSetUp baseUiSetup)
{
	OnEnableInputs = baseUiSetup._onEnableInputs;
	OnDisableInputs = baseUiSetup._onDisableInputs;
	OnChangeScreen = baseUiSetup._onChangeScreen;
	CloseAnimationFinished();
}

void UBaseUI::Open()
{
	SetVisibility(ESlateVisibility::Visible);
	CallOpenAnimation();
}

void UBaseUI::Close()
{
	CallCloseAnimation();
}

void UBaseUI::CloseAnimationFinished()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Close");
	SetVisibility(ESlateVisibility::Hidden);
}

void UBaseUI::EnableInputs()
{
	if (OnEnableInputs)
		OnEnableInputs(this);
}

void UBaseUI::DisableInputs()
{
	if (OnDisableInputs)
		OnDisableInputs();
}

void UBaseUI::ChangeScreen(UIType screenType)
{
	if (OnChangeScreen)
		OnChangeScreen(screenType);
}

void UBaseUI::ButtonBackPressed()
{
}

void UBaseUI::ButtonConfirmPressed()
{
}

void UBaseUI::ButtonUpPressed()
{
}

void UBaseUI::ButtonDownPressed()
{
}

void UBaseUI::ButtonLeftPressed()
{
}

void UBaseUI::ButtonRightPressed()
{
}