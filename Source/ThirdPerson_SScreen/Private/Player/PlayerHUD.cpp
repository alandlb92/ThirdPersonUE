// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerHUD.h"
#include "Player/PState.h"
#include "Player/PlayerPawn.h"
#include "../ThirdPerson_SScreenGameModeBase.h"
#include "Blueprint/WidgetTree.h"
#include "Kismet/GameplayStatics.h"



void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();

	IsShowingMessage = false;
	UWorld* world = GetWorld();

	if (_pressStartUI)
	{
		if (_pressStartInstance == nullptr)
			_pressStartInstance = CreateWidget<UPressStartUI, UWorld>(GetWorld(), _pressStartUI);
		if (_pressStartInstance != nullptr)
		{
			_pressStartInstance->AddToPlayerScreen();
			_pressStartInstance->SetUp();
			_pressStartInstance->OnEnableInputs.AddDynamic(this, &APlayerHUD::HEnableInput);
			_pressStartInstance->OnDisableInputs.AddDynamic(this, &APlayerHUD::HDisableInput);
			_pressStartInstance->OnChangeScreen.AddDynamic(this, &APlayerHUD::ChangeScreen);

		}
	}

	if (_setUpUI)
	{
		if (_setUpInstance == nullptr)
			_setUpInstance = CreateWidget<USetUpUI, UWorld>(GetWorld(), _setUpUI);



		if (_setUpInstance != nullptr)
		{
			_setUpInstance->AddToPlayerScreen();
			_setUpInstance->SetUp();
			_setUpInstance->OnEnableInputs.AddDynamic(this, &APlayerHUD::HEnableInput);
			_setUpInstance->OnDisableInputs.AddDynamic(this, &APlayerHUD::HDisableInput);
			_setUpInstance->OnChangeScreen.AddDynamic(this, &APlayerHUD::ChangeScreen);
			_setUpInstance->OnStartGamePlay.AddDynamic(this, &APlayerHUD::StartGamePlay);
		}
	}

	if (_gamePlayUI)
	{
		if (_gamePlayInstace == nullptr)
			_gamePlayInstace = CreateWidget<UGameplayUI, UWorld>(GetWorld(), _gamePlayUI);

		if (_gamePlayInstace != nullptr)
		{
			_gamePlayInstace->AddToPlayerScreen();
			_gamePlayInstace->SetUp();
			_gamePlayInstace->OnEnableInputs.AddDynamic(this, &APlayerHUD::HEnableInput);
			_gamePlayInstace->OnDisableInputs.AddDynamic(this, &APlayerHUD::HDisableInput);
			_gamePlayInstace->OnChangeScreen.AddDynamic(this, &APlayerHUD::ChangeScreen);
			_gamePlayInstace->DisableInteractMsg();
			_gamePlayInstace->HideText();
			Cast<APlayerPawn>(GetOwningPawn())->OnShowTextInteract.AddDynamic(_gamePlayInstace, &UGameplayUI::ShowText);
			Cast<APlayerPawn>(GetOwningPawn())->OnHideTextInteract.AddDynamic(_gamePlayInstace, &UGameplayUI::HideText);
		}
	}


	ChangeScreen(UIType::START);
}

void APlayerHUD::EnableInteractMsg()
{
	if (_gamePlayInstace != nullptr)
		_gamePlayInstace->EnableInteractMsg();
}

void APlayerHUD::DisableInteractMsg()
{
	if (_gamePlayInstace != nullptr)
		_gamePlayInstace->DisableInteractMsg();
}

void APlayerHUD::ShowText(FString text)
{
	if (_gamePlayInstace != nullptr)
	{
		_gamePlayInstace->ShowText(text);
		IsShowingMessage = true;
	}
}

void APlayerHUD::HideText()
{
	if (_gamePlayInstace != nullptr)
	{
		_gamePlayInstace->HideText();
		IsShowingMessage = false;
	}
}

void APlayerHUD::HEnableInput(UUIBase* UIReference)
{
	_currentUIinControll = UIReference;
}

void APlayerHUD::HDisableInput()
{
	_lastUIControll = _currentUIinControll;
	_currentUIinControll = nullptr;
}

void APlayerHUD::ChangeScreen(UIType uiType)
{

	if (_lastUIControll)
		_lastUIControll->Close();

	switch (uiType)
	{
	case UIType::START:
		if (_pressStartInstance)
			_pressStartInstance->Open();
		break;
	case UIType::SETUP:
		if (_setUpInstance)
			_setUpInstance->Open();
		break;
	case UIType::GAMEPLAY:
		_gamePlayInstace->Open();
		break;
	default:
		break;
	}
}

void APlayerHUD::StartGamePlay()
{
	APlayerPawn* _playerPawn = Cast<APlayerPawn>(GetOwningPawn());
	if (_playerPawn)
	{
		_playerPawn->StartGameplay();
	}

	_currentUIinControll->DisableInputs();
	ChangeScreen(UIType::GAMEPLAY);
}

void APlayerHUD::ButtonBackPressed()
{
	if (_currentUIinControll)
		_currentUIinControll->ButtonBackPressed();
}

void APlayerHUD::ButtonConfirmPressed()
{
	if (_currentUIinControll)
		_currentUIinControll->ButtonConfirmPressed();
}

void APlayerHUD::ButtonStartPressed()
{
	if (_currentUIinControll)
		_currentUIinControll->ButtonStartPressed();
}

void APlayerHUD::ButtonUpPressed()
{
	if (_currentUIinControll)
		_currentUIinControll->ButtonUpPressed();
}

void APlayerHUD::ButtonDownPressed()
{
	if (_currentUIinControll)
		_currentUIinControll->ButtonDownPressed();
}

void APlayerHUD::ButtonLeftPressed()
{
	if (_currentUIinControll)
		_currentUIinControll->ButtonLeftPressed();
}

void APlayerHUD::ButtonRightPressed()
{
	if (_currentUIinControll)
		_currentUIinControll->ButtonRightPressed();
}

void APlayerHUD::ButtonPPressed()
{
	if (_currentUIinControll)
		_currentUIinControll->ButtonPPressed();
}