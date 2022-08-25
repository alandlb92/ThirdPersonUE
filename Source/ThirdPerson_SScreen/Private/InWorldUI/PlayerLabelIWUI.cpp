// Fill out your copyright notice in the Description page of Project Settings.


#include "InWorldUI/PlayerLabelIWUI.h"

void UPlayerLabelIWUI::SetLabel(FString text)
{
	_playerNameText->SetText(FText::FromString(text));
}
