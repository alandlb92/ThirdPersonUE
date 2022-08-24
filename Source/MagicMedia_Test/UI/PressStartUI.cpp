// Fill out your copyright notice in the Description page of Project Settings.


#include "PressStartUI.h"
#include "PlayerHUD.h"

void UPressStartUI::AnimationStartPressedFinished()
{
	ChangeScreen(UIType::SETUP);
}

void UPressStartUI::ButtonConfirmPressed()
{
	CallStartPressed();
}

void UPressStartUI::ButtonStartPressed()
{
	CallStartPressed();
}