// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseUI.h"
#include <functional>
#include "Components/TextBlock.h"
#include "Components/Spacer.h"
#include "Components/SizeBox.h"
#include "VirtualKeyboardUI.h"
#include "Kismet/GameplayStatics.h"
#include "../Player/PState.h"
#include "SetUpUI.generated.h"


UCLASS()
class MAGICMEDIA_TEST_API USetUpUI : public UBaseUI
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
	class AMainGameMode* _gameMode;

	APState* GetPlayerState();
};
