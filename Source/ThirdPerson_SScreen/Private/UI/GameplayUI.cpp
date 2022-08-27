// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameplayUI.h"

void UGameplayUI::EnableInteractMsg()
{
	_inputs->SetRenderOpacity(1);
}

void UGameplayUI::DisableInteractMsg()
{
	_inputs->SetRenderOpacity(0);
}

void UGameplayUI::ShowText(FString text)
{
	_generalMesage->SetText(FText::FromString(text));
	_message->SetRenderOpacity(1);
}

void UGameplayUI::HideText()
{
	_message->SetRenderOpacity(0);
}