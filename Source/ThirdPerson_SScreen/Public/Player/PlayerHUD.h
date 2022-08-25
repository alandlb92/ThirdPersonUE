// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/PressStartUI.h"
#include "UI/GameplayUI.h"
#include "UI/SetUpUI.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSON_SSCREEN_API APlayerHUD : public AHUD
{
	GENERATED_BODY()
	friend class UHUDManager;
public:
	void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UPressStartUI> _pressStartUI;
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<USetUpUI> _setUpUI;
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UGameplayUI> _gamePlayUI;

	void PlayerTwoIsEnable();

private:
	void ClearAllActions();
	void SetUpInputComponent();

	class UHUDManager* _hudManager;

	UUIBase* _currentUIinControll;
	UUIBase* _lastUIControll;
	UPressStartUI* _pressStartInstance;
	USetUpUI* _setUpInstance;
	UGameplayUI* _gamePlayInstace;

	void EnableInput(UUIBase* UIReference);
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
