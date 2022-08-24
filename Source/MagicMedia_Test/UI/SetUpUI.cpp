// Fill out your copyright notice in the Description page of Project Settings.


#include "SetUpUI.h"
#include "UIManager.h"
#include "../Gameplay/MainGameMode.h"
#include "../Player/PlyerManager.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerInput.h"
#include "Kismet/GameplayStatics.h"

void USetUpUI::NativeConstruct()
{
	Super::NativeConstruct();
	_textMesage->SetText(FText(FText::FromString("Write you name")));
}

void USetUpUI::DisableAddPlayerTwoBox()
{
	_player2Box->SetVisibility(ESlateVisibility::Hidden);
}


void  USetUpUI::BeginPlay()
{
	_gameMode = Cast<AMainGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	UpdateAllGeneralMessage();
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
	else if (_gameMode->GetPlayerManager()->AllPlayerIsReady())
	{
		_gameMode->StartGameplay();
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
	if (_gameMode->GetPlayerManager()->GetPlayerCount() == 1)
	{
		_gameMode->GetPlayerManager()->CreatePlayer2(GetWorld());
		_gameMode->GetHUDManager()->PlayerTwoIsEnable();
	}
}

void USetUpUI::UpdateAllGeneralMessage()
{
	_gameMode->GetHUDManager()->UpdateAllSetUpWidget();
}

void USetUpUI::UpdateGeneralMessage()
{
	UE_LOG(LogTemp, Warning, TEXT("UpdateGeneralMessage  player id: %i"), GetPlayerState()->GetPlayerId());
	UE_LOG(LogTemp, Warning, TEXT("All players are ready: %s"), _gameMode->GetPlayerManager()->AllPlayerIsReady() ? TEXT("true") : TEXT("false"));
	FString message;
	if (GetPlayerState()->GetPlayerId() == 0)
	{
		if (_gameMode->GetPlayerManager()->AllPlayerIsReady())
		{
			message.Append("Press Start");
		}
		else
		{
			message.Append("Waiting Players");
		}
	}
	_generalMessage->SetText(FText::FromString(message));
}

void USetUpUI::SetPlayerReady(bool isReady)
{
	_virtualKeyBoard->SetVisibility(isReady ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
	FString name = _virtualKeyBoard->GetText();
	FString text;
	text.Append(name);
	text.Append(isReady ? " is Ready!" : "Write you name");
	_textMesage->SetText(FText::FromString(text));
	GetPlayerState()->ready = isReady;
	GetPlayerState()->name = name;
	UpdateAllGeneralMessage();
}

APState* USetUpUI::GetPlayerState()
{
	APlayerController* owning = GetOwningPlayer();
	
	if (owning)
		return owning->GetPlayerState<APState>();
	else
		return nullptr;
}