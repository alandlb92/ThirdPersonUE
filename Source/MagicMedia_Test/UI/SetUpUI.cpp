// Fill out your copyright notice in the Description page of Project Settings.


#include "SetUpUI.h"

void USetUpUI::NativeConstruct()
{
	Super::NativeConstruct();

	_playerOneTextMesage->SetText(FText(FText::FromString("Write you name")));
	_playerTwoTextMesage->SetText(FText(FText::FromString("Press A to join")));
	_playerTwoVirtualKeyBoard->SetVisibility(ESlateVisibility::Hidden);
}

void USetUpUI::ButtonConfirmPressed_Player2()
{
	_playerTwoTextMesage->SetText(FText(FText::FromString("Write you name")));
	_playerTwoVirtualKeyBoard->SetVisibility(ESlateVisibility::Visible);
}

void USetUpUI::ButtonBackPressed_Player1()
{
	_playerOneVirtualKeyBoard->BackSpace();	
}

void USetUpUI::ButtonConfirmPressed_Player1()
{
	_playerOneVirtualKeyBoard->Select();
}

void USetUpUI::ButtonUpPressed_Player1()
{
	_playerOneVirtualKeyBoard->UptKey();
}

void USetUpUI::ButtonDownPressed_Player1()
{
	_playerOneVirtualKeyBoard->DownKey();
}

void USetUpUI::ButtonLeftPressed_Player1()
{
	_playerOneVirtualKeyBoard->LefttKey();
}

void USetUpUI::ButtonRightPressed_Player1()
{
	_playerOneVirtualKeyBoard->RightKey();
}