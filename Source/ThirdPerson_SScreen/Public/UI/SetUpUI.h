// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UIBase.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "UI/VirtualKeyboardUI.h"
#include "Player/PState.h"
#include "SetUpUI.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartGamePlay);

UCLASS()
class THIRDPERSON_SSCREEN_API USetUpUI : public UUIBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* _textMesage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UVirtualKeyboardUI* _virtualKeyBoard;

	void NativeConstruct() override;

	void ButtonBackPressed() override;
	void ButtonConfirmPressed() override;
	void ButtonStartPressed() override;

	void ButtonUpPressed() override;
	void ButtonDownPressed() override;
	void ButtonLeftPressed() override;
	void ButtonRightPressed() override;
	void ButtonPPressed() override;

	FOnStartGamePlay OnStartGamePlay;

private:
	void SetPlayerReady(bool isReady);

	APState* GetPlayerState();

};
