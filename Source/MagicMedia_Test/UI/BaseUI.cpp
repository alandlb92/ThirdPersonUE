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

void UBaseUI::ButtonBackPressed_Player1()
{
}

void UBaseUI::ButtonConfirmPressed_Player1()
{
}

void UBaseUI::ButtonUpPressed_Player1()
{
}

void UBaseUI::ButtonDownPressed_Player1()
{
}

void UBaseUI::ButtonLeftPressed_Player1()
{
}

void UBaseUI::ButtonRightPressed_Player1()
{
}


void UBaseUI::ButtonBackPressed_Player2()
{
}

void UBaseUI::ButtonConfirmPressed_Player2()
{
}

void UBaseUI::ButtonUpPressed_Player2()
{
}

void UBaseUI::ButtonDownPressed_Player2()
{
}

void UBaseUI::ButtonLeftPressed_Player2()
{
}

void UBaseUI::ButtonRightPressed_Player2()
{
}