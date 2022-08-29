// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SetUpUI.h"
#include "Kismet/GameplayStatics.h"


void USetUpUI::NativeConstruct()
{
	Super::NativeConstruct();
	_textMesage->SetText(FText(FText::FromString("Write your name")));
}

void USetUpUI::ButtonBackPressed()
{
	if (!GetPlayerState()->ready)
		_virtualKeyBoard->BackSpace();
	else
		SetPlayerReady(false);
}

void USetUpUI::ButtonConfirmPressed()
{
	if (!GetPlayerState()->ready)
		_virtualKeyBoard->Select();
}

void USetUpUI::ButtonStartPressed()
{
	if (!_virtualKeyBoard->GetText().IsEmpty() && !GetPlayerState()->ready)
	{
		SetPlayerReady(true);
	}
	else if(GetPlayerState()->ready)
	{
		OnStartGamePlay.Broadcast();
	}
}

void USetUpUI::ButtonUpPressed()
{
	if (!GetPlayerState()->ready)
		_virtualKeyBoard->UpKey();
}

void USetUpUI::ButtonDownPressed()
{
	if (!GetPlayerState()->ready)
		_virtualKeyBoard->DownKey();
}

void USetUpUI::ButtonLeftPressed()
{
	if (!GetPlayerState()->ready)
		_virtualKeyBoard->LefttKey();
}

void USetUpUI::ButtonRightPressed()
{
	if (!GetPlayerState()->ready)
		_virtualKeyBoard->RightKey();
	else
		UE_LOG(LogTemp, Warning, TEXT("player not joined"))
}


void USetUpUI::ButtonPPressed()
{
	UGameplayStatics::CreatePlayer(GetWorld());
}


void USetUpUI::SetPlayerReady(bool isReady)
{
	FString name = isReady ? _virtualKeyBoard->GetText() : "";
	FString text;

	_virtualKeyBoard->SetRenderOpacity(!isReady);

	text.Append(name);
	text.Append(isReady ? " is Ready! press enter to continue" : "Write your name");
	_textMesage->SetText(FText::FromString(text));
	GetPlayerState()->ready = isReady;
	GetPlayerState()->name = name;
}

APState* USetUpUI::GetPlayerState()
{
	APlayerController* owning = GetOwningPlayer();

	if (owning)
		return owning->GetPlayerState<APState>();
	else
		return nullptr;
}