// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UIBase.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "UI/VirtualKeyboardUI.h"
#include "Player/PState.h"
#include "SetUpUI.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSON_SSCREEN_API USetUpUI : public UUIBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* _generalMessage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* _textMesage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UVirtualKeyboardUI* _virtualKeyBoard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UBorder* _player2Box;

	void NativeConstruct() override;
	void BeginPlay();

	void ButtonBackPressed() override;
	void ButtonConfirmPressed() override;
	void ButtonStartPressed() override;

	void ButtonUpPressed() override;
	void ButtonDownPressed() override;
	void ButtonLeftPressed() override;
	void ButtonRightPressed() override;
	void ButtonPPressed() override;

	void DisableAddPlayerTwoBox();
	void UpdateGeneralMessage();

private:
	void UpdateAllGeneralMessage();
	void SetPlayerReady(bool isReady);
	class AThirdPerson_SScreenGameModeBase* _gameMode;

	APState* GetPlayerState();

};
