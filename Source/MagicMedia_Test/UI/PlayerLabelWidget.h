// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "PlayerLabelWidget.generated.h"

/**
 * 
 */
UCLASS()
class MAGICMEDIA_TEST_API UPlayerLabelWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* _playerNameText;
	void SetLabel(FString text);
	
};
