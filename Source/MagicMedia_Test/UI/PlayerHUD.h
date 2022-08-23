// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PressStartUI.h"
#include "SetUpUI.h"
#include "PlayerHUD.generated.h"


UENUM()
enum UIType
{
	START,
	SETUP,
	HUD
};

UCLASS()
class MAGICMEDIA_TEST_API APlayerHUD : public AHUD
{
	GENERATED_BODY()
	friend class UUIManager;
public:
	void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UPressStartUI> _pressStartUI;
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<USetUpUI> _setUpUI;

	void PlayerTwoIsEnable();

private:
	void SetUpInputComponent();

	class UUIManager* _uiManager;

	UBaseUI* _currentUIinControll;
	UBaseUI* _lastUIControll;
	UPressStartUI* _pressStartInstance;
	USetUpUI* _setUpInstance;

	void EnableInput(UBaseUI* UIReference);
	void DisableInput();
	void ChangeScreen(UIType uiType);

	void ButtonBackPressed();
	void ButtonConfirmPressed();
	void ButtonStartPressed();
	void ButtonUpPressed();
	void ButtonDownPressed();
	void ButtonLeftPressed();
	void ButtonRightPressed();
	void ButtonPPressed();
};
