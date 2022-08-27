// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "PlayerLabelIWUI.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSON_SSCREEN_API UPlayerLabelIWUI : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* _playerNameText;
	UFUNCTION(NetMulticast, Reliable)
	void SetLabel(const FString& text);
	
};
