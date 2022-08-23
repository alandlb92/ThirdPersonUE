// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManager.h"

void AUIManager::BeginPlay()
{
	Super::BeginPlay();
	if (_pressStartUI && _setUpUI && PlayerOwner == GetWorld()->GetFirstPlayerController())
	{
		if (_pressStartInstance == nullptr)
			_pressStartInstance = CreateWidget<UPressStartUI>(GetWorld(), _pressStartUI);
		if (_pressStartInstance != nullptr)
		{
			_pressStartInstance->AddToViewport();
			_pressStartInstance->SetUp(BaseUiSetUp{
					std::bind(&AUIManager::EnableInput, this, std::placeholders::_1),
					std::bind(&AUIManager::DisableInput, this),
					std::bind(&AUIManager::ChangeScreen, this, std::placeholders::_1)
				});
		}

		if (_setUpInstance == nullptr)
			_setUpInstance = CreateWidget<USetUpUI>(GetWorld(), _setUpUI);

		if (_setUpInstance != nullptr)
		{
			_setUpInstance->AddToViewport();
			_setUpInstance->SetUp(BaseUiSetUp{
					std::bind(&AUIManager::EnableInput, this, std::placeholders::_1),
					std::bind(&AUIManager::DisableInput, this),
					std::bind(&AUIManager::ChangeScreen, this, std::placeholders::_1)
				});
		}
	}

	SetUpInputComponent();
	ChangeScreen(UIType::START);
}

void AUIManager::SetUpInputComponent()
{
	if (!_playerOneController) {		
		_playerOneController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		_playerTwoController = UGameplayStatics::GetPlayerController(GetWorld(), 1);		
	}

	if (_playerOneController) {
		_playerOneController->InputComponent->BindAction("UIConfirm", IE_Pressed, this, &AUIManager::ButtonConfirmPressed_Player1);
		_playerOneController->InputComponent->BindAction("UIBack", IE_Pressed, this, &AUIManager::ButtonBackPressed_Player1);
		_playerOneController->InputComponent->BindAction("UIUp", IE_Pressed, this, &AUIManager::ButtonUpPressed_Player1);
		_playerOneController->InputComponent->BindAction("UIDown", IE_Pressed, this, &AUIManager::ButtonDownPressed_Player1);
		_playerOneController->InputComponent->BindAction("UILeft", IE_Pressed, this, &AUIManager::ButtonLeftPressed_Player1);
		_playerOneController->InputComponent->BindAction("UIRight", IE_Pressed, this, &AUIManager::ButtonRightPressed_Player1);
	}

	if (_playerTwoController)
	{
		_playerTwoController->InputComponent->BindAction("UIConfirm", IE_Pressed, this, &AUIManager::ButtonConfirmPressed_Player2);
		_playerTwoController->InputComponent->BindAction("UIBack", IE_Pressed, this, &AUIManager::ButtonBackPressed_Player2);
		_playerTwoController->InputComponent->BindAction("UIUp", IE_Pressed, this, &AUIManager::ButtonUpPressed_Player2);
		_playerTwoController->InputComponent->BindAction("UIDown", IE_Pressed, this, &AUIManager::ButtonDownPressed_Player2);
		_playerTwoController->InputComponent->BindAction("UILeft", IE_Pressed, this, &AUIManager::ButtonLeftPressed_Player2);
		_playerTwoController->InputComponent->BindAction("UIRight", IE_Pressed, this, &AUIManager::ButtonRightPressed_Player2);
	}
}

void AUIManager::EnableInput(UBaseUI* UIReference)
{
	_currentUIinControll = UIReference;

}

void AUIManager::DisableInput()
{
	_lastUIControll = _currentUIinControll;
	_currentUIinControll = nullptr;
}


void AUIManager::ChangeScreen(UIType uiType)
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
	case UIType::HUD:
		break;
	}
}

void AUIManager::ButtonBackPressed_Player1()
{
	if (_currentUIinControll)
		_currentUIinControll->ButtonBackPressed_Player1();
}

void AUIManager::ButtonConfirmPressed_Player1()
{
	if (_currentUIinControll)
		_currentUIinControll->ButtonConfirmPressed_Player1();
}

void AUIManager::ButtonUpPressed_Player1()
{
	if (_currentUIinControll)
		_currentUIinControll->ButtonUpPressed_Player1();
}

void AUIManager::ButtonDownPressed_Player1()
{
	if (_currentUIinControll)
		_currentUIinControll->ButtonDownPressed_Player1();
}

void AUIManager::ButtonLeftPressed_Player1()
{
	if (_currentUIinControll)
		_currentUIinControll->ButtonLeftPressed_Player1();
}

void AUIManager::ButtonRightPressed_Player1()
{
	if (_currentUIinControll)
		_currentUIinControll->ButtonRightPressed_Player1();
}


void AUIManager::ButtonBackPressed_Player2()
{
	if (_currentUIinControll)
		_currentUIinControll->ButtonBackPressed_Player2();
}

void AUIManager::ButtonConfirmPressed_Player2()
{
	if (_currentUIinControll)
		_currentUIinControll->ButtonConfirmPressed_Player2();
}

void AUIManager::ButtonUpPressed_Player2()
{
	if (_currentUIinControll)
		_currentUIinControll->ButtonUpPressed_Player2();
}

void AUIManager::ButtonDownPressed_Player2()
{
	if (_currentUIinControll)
		_currentUIinControll->ButtonDownPressed_Player2();
}

void AUIManager::ButtonLeftPressed_Player2()
{
	if (_currentUIinControll)
		_currentUIinControll->ButtonLeftPressed_Player2();
}

void AUIManager::ButtonRightPressed_Player2()
{
	if (_currentUIinControll)
		_currentUIinControll->ButtonRightPressed_Player2();
}