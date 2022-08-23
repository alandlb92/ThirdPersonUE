// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PressStartUI.h"
#include "SetUpUI.h"
#include "UIManager.generated.h"


UENUM()
enum UIType
{
	START,
	SETUP,
	HUD
};

UCLASS()
class MAGICMEDIA_TEST_API AUIManager : public AHUD
{
	GENERATED_BODY()
public:
	void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UPressStartUI> _pressStartUI;
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<USetUpUI> _setUpUI;

private:
	void SetUpInputComponent();

	APlayerController* _playerOneController;
	APlayerController* _playerTwoController;

	UBaseUI* _currentUIinControll;
	UBaseUI* _lastUIControll;
	UPressStartUI* _pressStartInstance;
	USetUpUI* _setUpInstance;

	void EnableInput(UBaseUI* UIReference);
	void DisableInput();
	void ChangeScreen(UIType uiType);
	
	void ButtonBackPressed_Player1();
	void ButtonConfirmPressed_Player1();
	void ButtonUpPressed_Player1();
	void ButtonDownPressed_Player1();
	void ButtonLeftPressed_Player1();
	void ButtonRightPressed_Player1();

	void ButtonBackPressed_Player2();
	void ButtonConfirmPressed_Player2();
	void ButtonUpPressed_Player2();
	void ButtonDownPressed_Player2();
	void ButtonLeftPressed_Player2();
	void ButtonRightPressed_Player2();

};
