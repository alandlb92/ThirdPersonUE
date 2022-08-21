// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManager.h"

void AUIManager::BeginPlay()
{
	Super::BeginPlay();
	if (_pressStartUI)
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
	if (!_firstPlayerController) {
		_firstPlayerController = GetWorld()->GetFirstPlayerController();
	}

	if (_firstPlayerController) {
		_firstPlayerController->InputComponent->BindAction("UIConfirm", IE_Pressed, this, &AUIManager::ButtonConfirmPressed);
		_firstPlayerController->InputComponent->BindAction("UIBack", IE_Pressed, this, &AUIManager::ButtonBackPressed);

		_firstPlayerController->InputComponent->BindAction("UIUp", IE_Pressed, this, &AUIManager::ButtonUpPressed);
		_firstPlayerController->InputComponent->BindAction("UIDown", IE_Pressed, this, &AUIManager::ButtonDownPressed);
		_firstPlayerController->InputComponent->BindAction("UILeft", IE_Pressed, this, &AUIManager::ButtonLeftPressed);
		_firstPlayerController->InputComponent->BindAction("UIRight", IE_Pressed, this, &AUIManager::ButtonRightPressed);
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
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "ChangeScreen");
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

void AUIManager::ButtonBackPressed()
{
	if (_currentUIinControll)
		_currentUIinControll->ButtonBackPressed();
}

void AUIManager::ButtonConfirmPressed()
{
	if (_currentUIinControll)
		_currentUIinControll->ButtonConfirmPressed();
}

void AUIManager::ButtonUpPressed()
{
	if (_currentUIinControll)
		_currentUIinControll->ButtonUpPressed();
}

void AUIManager::ButtonDownPressed()
{
	if (_currentUIinControll)
		_currentUIinControll->ButtonDownPressed();
}

void AUIManager::ButtonLeftPressed()
{
	if (_currentUIinControll)
		_currentUIinControll->ButtonLeftPressed();
}

void AUIManager::ButtonRightPressed()
{
	if (_currentUIinControll)
		_currentUIinControll->ButtonRightPressed();
}
