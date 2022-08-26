// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SetUpUI.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/LevelManager.h"
#include "Managers/PlayerManager.h"


void USetUpUI::NativeConstruct()
{
	Super::NativeConstruct();
}

void USetUpUI::DisableAddPlayerTwoBox()
{
	_player2Box->SetVisibility(ESlateVisibility::Collapsed);
	_player2Box->SetVisibility(ESlateVisibility::Hidden);
}


void  USetUpUI::SetUp()
{
	Super::SetUp();
	_textMesage->SetText(FText(FText::FromString("Write you name")));
	_levelManager = Cast<ALevelManager>(GetWorld()->GetLevelScriptActor());
	_virtualKeyBoard->SetUp();
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
	else
	{
		OnStartGamePlay.Broadcast();
	}
}

void USetUpUI::ButtonUpPressed()
{
	if (!GetPlayerState()->ready)
		_virtualKeyBoard->UptKey();
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
	_player2Box->SetVisibility(ESlateVisibility::Collapsed);
	_player2Box->SetVisibility(isReady ? ESlateVisibility::Hidden : ESlateVisibility::Visible);

	FString name = _virtualKeyBoard->GetText();
	FString text;
	text.Append(name);
	text.Append(isReady ? " is Ready!" : "Write you name");
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