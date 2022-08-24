// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerLabelWidget.h"


void UPlayerLabelWidget::SetLabel(FString text)
{
	_playerNameText->SetText(FText::FromString(text));
}