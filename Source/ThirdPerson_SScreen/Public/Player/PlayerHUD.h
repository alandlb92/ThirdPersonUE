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
public:
	void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UPressStartUI> _pressStartUI;
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<USetUpUI> _setUpUI;
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UGameplayUI> _gamePlayUI;
		
	void EnableInteractMsg();
	void DisableInteractMsg();
	void ShowText(FString text);
	void HideText();
	bool IsShowingMessage;

	void ButtonBackPressed();
	void ButtonConfirmPressed();
	void ButtonStartPressed();
	void ButtonUpPressed();
	void ButtonDownPressed();
	void ButtonLeftPressed();
	void ButtonRightPressed();
	void ButtonPPressed();

private:

	class UHUDManager* _hudManager;
	UUIBase* _currentUIinControll;
	UUIBase* _lastUIControll;
	UPressStartUI* _pressStartInstance;
	USetUpUI* _setUpInstance;
	UGameplayUI* _gamePlayInstace;

	UFUNCTION()
	void HEnableInput(UUIBase* UIReference);	
	UFUNCTION()
	void HDisableInput();	
	UFUNCTION()
	void ChangeScreen(UIType uiType);
	UFUNCTION()
	void StartGamePlay();
};
