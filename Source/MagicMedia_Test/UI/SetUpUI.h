// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseUI.h"
#include "Components/TextBlock.h"
#include "Components/SizeBox.h"
#include "VirtualKeyboardUI.h"
#include "Kismet/GameplayStatics.h"
#include "SetUpUI.generated.h"

/**
 *
 */
UCLASS()
class MAGICMEDIA_TEST_API USetUpUI : public UBaseUI
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* _playerOneTextMesage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* _playerTwoTextMesage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UVirtualKeyboardUI* _playerOneVirtualKeyBoard;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UVirtualKeyboardUI* _playerTwoVirtualKeyBoard;

	void NativeConstruct() override;

	void ButtonBackPressed_Player1() override;
	void ButtonConfirmPressed_Player1() override;
	void ButtonUpPressed_Player1() override;
	void ButtonDownPressed_Player1() override;
	void ButtonLeftPressed_Player1() override;
	void ButtonRightPressed_Player1() override;


	void ButtonConfirmPressed_Player2() override;
};
