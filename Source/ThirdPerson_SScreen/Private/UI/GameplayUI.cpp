// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameplayUI.h"

void UGameplayUI::EnableInteractMsg()
{
	_inputs->SetVisibility(ESlateVisibility::Collapsed);
	_inputs->SetVisibility(ESlateVisibility::Visible);
}

void UGameplayUI::DisableInteractMsg()
{
	_inputs->SetVisibility(ESlateVisibility::Collapsed);
	_inputs->SetVisibility(ESlateVisibility::Hidden);
}

void UGameplayUI::ShowText(FString text)
{
	_generalMesage->SetText(FText::FromString(text));
	_message->SetVisibility(ESlateVisibility::Collapsed);
	_message->SetVisibility(ESlateVisibility::Visible);
}

void UGameplayUI::HideText()
{
	_message->SetVisibility(ESlateVisibility::Collapsed);
	_message->SetVisibility(ESlateVisibility::Hidden);
}