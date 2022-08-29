// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UIBase.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "GameplayUI.generated.h"

/**
 *
 */
UCLASS()
class THIRDPERSON_SSCREEN_API UGameplayUI : public UUIBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* _generalMesage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UBorder* _inputs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UBorder* _message;

	void EnableInteractMsg();
	void DisableInteractMsg();
	UFUNCTION()
	void ShowText(FString text);
	UFUNCTION()
	void HideText();

};
