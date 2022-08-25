// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerHUD.h"
#include "Player/PState.h"
#include "../ThirdPerson_SScreenGameModeBase.h"
#include "Managers/HUDManager.h"
#include "Kismet/GameplayStatics.h"


void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();

	_hudManager = Cast<AThirdPerson_SScreenGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GetHUDManager();
	_hudManager->Register(this);

	if (_pressStartUI && PlayerOwner == GetWorld()->GetFirstPlayerController())
	{
		if (_pressStartInstance == nullptr)
			_pressStartInstance = CreateWidget<UPressStartUI, APlayerController>(PlayerOwner, _pressStartUI);
		if (_pressStartInstance != nullptr)
		{
			_pressStartInstance->AddToPlayerScreen();
			_pressStartInstance->SetUp(BaseUiSetUp{
					std::bind(&APlayerHUD::EnableInput, this, std::placeholders::_1),
					std::bind(&APlayerHUD::DisableInput, this),
					std::bind(&UHUDManager::ChangeAllPlayersScreen, _hudManager, std::placeholders::_1)
				});
		}
	}

	if (_setUpUI)
	{
		if (_setUpInstance == nullptr)
			_setUpInstance = CreateWidget<USetUpUI, APlayerController>(PlayerOwner, _setUpUI);



		if (_setUpInstance != nullptr)
		{
			_setUpInstance->AddToPlayerScreen();
			_setUpInstance->SetUp(BaseUiSetUp{
					std::bind(&APlayerHUD::EnableInput, this, std::placeholders::_1),
					std::bind(&APlayerHUD::DisableInput, this),
					std::bind(&APlayerHUD::ChangeScreen, this, std::placeholders::_1)
				});
		}
	}

	if (_gamePlayUI)
	{
		if (_gamePlayInstace == nullptr)
			_gamePlayInstace = CreateWidget<UGameplayUI, APlayerController>(PlayerOwner, _gamePlayUI);

		if (_gamePlayInstace != nullptr)
		{
			_gamePlayInstace->AddToPlayerScreen();
			_gamePlayInstace->SetUp(BaseUiSetUp{
					std::bind(&APlayerHUD::EnableInput, this, std::placeholders::_1),
					std::bind(&APlayerHUD::DisableInput, this),
					std::bind(&APlayerHUD::ChangeScreen, this, std::placeholders::_1)
				});
		}
	}


	SetUpInputComponent();
	_setUpInstance->BeginPlay();
	if (PlayerOwner->GetPlayerState<APState>()->GetPlayerId() == 0)
		ChangeScreen(UIType::START);
	else
		ChangeScreen(UIType::SETUP);
}

void APlayerHUD::PlayerTwoIsEnable()
{
	_setUpInstance->DisableAddPlayerTwoBox();
}

void APlayerHUD::ClearAllActions()
{
	GetOwningPlayerController()->InputComponent->ClearActionBindings();
}

void APlayerHUD::SetUpInputComponent()
{	
	GetOwningPlayerController()->InputComponent->BindAction("UIConfirm", IE_Pressed, this, &APlayerHUD::ButtonConfirmPressed);
	GetOwningPlayerController()->InputComponent->BindAction("UIStart", IE_Pressed, this, &APlayerHUD::ButtonStartPressed);
	GetOwningPlayerController()->InputComponent->BindAction("UIBack", IE_Pressed, this, &APlayerHUD::ButtonBackPressed);
	GetOwningPlayerController()->InputComponent->BindAction("UIUp", IE_Pressed, this, &APlayerHUD::ButtonUpPressed);
	GetOwningPlayerController()->InputComponent->BindAction("UIDown", IE_Pressed, this, &APlayerHUD::ButtonDownPressed);
	GetOwningPlayerController()->InputComponent->BindAction("UILeft", IE_Pressed, this, &APlayerHUD::ButtonLeftPressed);
	GetOwningPlayerController()->InputComponent->BindAction("UIRight", IE_Pressed, this, &APlayerHUD::ButtonRightPressed);
	GetOwningPlayerController()->InputComponent->BindAction("JoinPlayer2", IE_Pressed, this, &APlayerHUD::ButtonPPressed);
}

void APlayerHUD::EnableInput(UUIBase* UIReference)
{
	_currentUIinControll = UIReference;

}

void APlayerHUD::DisableInput()
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