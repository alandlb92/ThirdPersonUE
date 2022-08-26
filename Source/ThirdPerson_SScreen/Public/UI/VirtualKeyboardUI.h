// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/GridPanel.h"
#include "Components/Border.h"
#include <map>
#include "VirtualKeyboardUI.generated.h"

UENUM()
enum class SlotState : uint8
{
	SELECTED,
	NOT_SELECTED
};

USTRUCT()
struct THIRDPERSON_SSCREEN_API FKeySlot
{
	GENERATED_USTRUCT_BODY()
public:
	FKeySlot(){}
	FKeySlot(UBorder* border, UTextBlock* text)
	{
		_border = border;
		_text = text;
	}

	UBorder* _border;
	UTextBlock* _text;
};

UCLASS()
class THIRDPERSON_SSCREEN_API UVirtualKeyboardUI : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativePreConstruct() override;
	void SetUp();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		FLinearColor borderUnselectedColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		FLinearColor fontUnselectedColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		FLinearColor borderSelectedColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		FLinearColor fontSelectedColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* _textResult;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UGridPanel* _keyboardButtons;

	FString GetText();

	void RightKey();
	void LefttKey();
	void UptKey();
	void DownKey();
	void Select();
	void BackSpace();

private:
	void UnselectAllButtons();
	void SetButtonCollors(SlotState slotState, FKeySlot* keySlot);
	void SetSelected(int indexSelected);
	int _indexSelected;
	std::map<int, FKeySlot*> _buttons;
	const int COLUNM_COUNT = 9;
	const int LETTERS_COUNT = 27;
	const FString _letters[27]{ "q", "w", "e", "r", "t", "y", "u", "i", "o",
								  "p", "a", "s", "d", "f", "g", "h", "j", "k",
								  "l", "z", "x", "c", "v", "b", "n", "m", "_" };
};
