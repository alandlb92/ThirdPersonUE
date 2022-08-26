// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIBase.h"


void UUIBase::SetUp()
{
	CloseAnimationFinished();
}

void UUIBase::Open()
{
	SetVisibility(ESlateVisibility::Collapsed);
	SetVisibility(ESlateVisibility::Visible);
	CallOpenAnimation();
}

void UUIBase::Close()
{
	CallCloseAnimation();
}

void UUIBase::CloseAnimationFinished()
{
	SetVisibility(ESlateVisibility::Collapsed);
	SetVisibility(ESlateVisibility::Hidden);
}

void UUIBase::EnableInputs()
{
	OnEnableInputs.Broadcast(this);
}

void UUIBase::DisableInputs()
{
	OnDisableInputs.Broadcast();
}

void UUIBase::ChangeScreen(UIType screenType)
{
	UE_LOG(LogTemp, Warning, TEXT("ChangeScreen"));
	OnChangeScreen.Broadcast(screenType);
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

