// Fill out your copyright notice in the Description page of Project Settings.


#include "PressStartUI.h"
#include "UIManager.h"

void UPressStartUI::AnimationStartPressedFinished()
{
	ChangeScreen(UIType::SETUP);
}

void UPressStartUI::ButtonConfirmPressed()
{
	CallStartPressed();
}