// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/RichTextBlock.h"
#include "Components/GridPanel.h"
#include "Components/Border.h"
#include <map>
#include "Engine/DataTable.h"
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
	FKeySlot(FString character, UBorder* border, URichTextBlock* text)
	{
		_character = character;
		_border = border;
		_text = text;
	}
	FString _character;
	UBorder* _border;
	URichTextBlock* _text;
};

UCLASS()
class THIRDPERSON_SSCREEN_API UVirtualKeyboardUI : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativePreConstruct() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* TextStyle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	FLinearColor borderUnselectedColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	FLinearColor borderSelectedColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	URichTextBlock* _textResult;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UGridPanel* _keyboardButtons;

	FString GetText();
	void RightKey();
	void LefttKey();
	void UpKey();
	void DownKey();
	void Select();
	void BackSpace();

private:

	void UnselectAllButtons();
	void SetButtonCollors(SlotState slotState, FKeySlot keySlot);
	void SetSelected(int indexSelected);
	int _indexSelected;
	UPROPERTY()
	TMap<int, FKeySlot> _buttons;
	const int COLUNM_COUNT = 9;
	const int LETTERS_COUNT = 27;
	const FString _letters[27]{ "q", "w", "e", "r", "t", "y", "u", "i", "o",
								  "p", "a", "s", "d", "f", "g", "h", "j", "k",
								  "l", "z", "x", "c", "v", "b", "n", "m", "_" };
};
