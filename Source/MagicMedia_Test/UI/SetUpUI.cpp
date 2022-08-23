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
	_player2Spacer->SetVisibility(ESlateVisibility::Hidden);
	_player2Box->SetVisibility(ESlateVisibility::Hidden);
}


void  USetUpUI::BeginPlay()
{
	_gameMode = Cast<AMainGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	UpdateGeneralMessage();
}

void USetUpUI::ButtonBackPressed()
{
	if (_virtualKeyBoard->GetText().IsEmpty() && GetPlayerState()->GetPlayerId() == 1)
		UE_LOG(LogTemp, Warning, TEXT("Player 2 UNJOIN"));

	if (!GetPlayerState()->ready && GetPlayerState()->joined)
		_virtualKeyBoard->BackSpace();
}

void USetUpUI::ButtonConfirmPressed()
{
	if (GetPlayerState()->GetPlayerId() == 1 && !GetPlayerState()->joined)
		UE_LOG(LogTemp, Warning, TEXT("Player 2 join"));

	if (!GetPlayerState()->ready && GetPlayerState()->joined)
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
		UE_LOG(LogTemp, Warning, TEXT("GO TO GAMEPLAY"));
	}
}

void USetUpUI::ButtonUpPressed()
{
	if (!GetPlayerState()->ready && GetPlayerState()->joined)
		_virtualKeyBoard->UptKey();
}

void USetUpUI::ButtonDownPressed()
{
	if (!GetPlayerState()->ready && GetPlayerState()->joined)
		_virtualKeyBoard->DownKey();
}

void USetUpUI::ButtonLeftPressed()
{
	if (!GetPlayerState()->ready && GetPlayerState()->joined)
		_virtualKeyBoard->LefttKey();
}

void USetUpUI::ButtonRightPressed()
{
	if (!GetPlayerState()->ready && GetPlayerState()->joined)
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

void USetUpUI::UpdateGeneralMessage()
{
	FString message;
	if (GetPlayerState()->GetPlayerId() == 0 && _gameMode->GetPlayerManager()->PlayerTwoIsJoined())
	{
		if (_gameMode->GetPlayerManager()->AllPlayerIsReady())
		{
			message.Append("Press Start");
		}
		else if (_gameMode->GetPlayerManager()->PlayerOneIsReady())
		{
			message.Append("Waiting Player 2");
		}
		else if (_gameMode->GetPlayerManager()->PlayerTwoIsReady())
		{
			message.Append("Waiting Player 1");
		}
		else
		{
			message.Append("Waiting Players");
		}
	}
	else if (GetPlayerState()->GetPlayerId() == 0)
	{
		if (_gameMode->GetPlayerManager()->PlayerOneIsReady())
		{
			message.Append("Press Start");
		}
		else
		{
			message.Append("Waiting Player 1");
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
	UpdateGeneralMessage();
}

APState* USetUpUI::GetPlayerState()
{
	return GetOwningPlayer()->GetPlayerState<APState>();
}