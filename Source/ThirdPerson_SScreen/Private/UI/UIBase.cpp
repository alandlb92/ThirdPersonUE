// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIBase.h"


void UUIBase::SetUp(BaseUiSetUp baseUiSetup)
{
	OnEnableInputs = baseUiSetup._onEnableInputs;
	OnDisableInputs = baseUiSetup._onDisableInputs;
	OnChangeScreen = baseUiSetup._onChangeScreen;
	CloseAnimationFinished();
}

void UUIBase::Open()
{
	SetVisibility(ESlateVisibility::Visible);
	CallOpenAnimation();
}

void UUIBase::Close()
{
	CallCloseAnimation();
}

void UUIBase::CloseAnimationFinished()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UUIBase::EnableInputs()
{
	if (OnEnableInputs)
		OnEnableInputs(this);
}

void UUIBase::DisableInputs()
{
	if (OnDisableInputs)
		OnDisableInputs();
}

void UUIBase::ChangeScreen(UIType screenType)
{
	UE_LOG(LogTemp, Warning, TEXT("ChangeScreen"));
	if (OnChangeScreen)
		OnChangeScreen(screenType);
}

void UUIBase::ButtonBackPressed()
{
}

void UUIBase::ButtonConfirmPressed()
{
}

void UUIBase::ButtonStartPressed()
{
}

void UUIBase::ButtonUpPressed()
{
}

void UUIBase::ButtonDownPressed()
{
}

void UUIBase::ButtonLeftPressed()
{
}

void UUIBase::ButtonRightPressed()
{
}

void UUIBase::ButtonPPressed()
{
}

