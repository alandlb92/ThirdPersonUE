// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PressStartUI.h"

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