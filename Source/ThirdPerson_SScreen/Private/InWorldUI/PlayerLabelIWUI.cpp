// Fill out your copyright notice in the Description page of Project Settings.


#include "InWorldUI/PlayerLabelIWUI.h"

void UPlayerLabelIWUI::SetLabel_Implementation(const FString& text)
{
	if (_playerNameText)
		_playerNameText->SetText(FText::FromString(text));
}
