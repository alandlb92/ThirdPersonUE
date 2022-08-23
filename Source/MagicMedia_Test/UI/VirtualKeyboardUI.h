// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseUI.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"
#include "Components/GridPanel.h"
#include "Components/Border.h"
#include <vector>
#include <map>
#include "Math/Color.h"
#include "VirtualKeyboardUI.generated.h"

enum class SlotState
{
	SELECTED,
	NOT_SELECTED
};

struct KeySlot
{
public:
	UBorder* _border;
	UTextBlock* _text;
};

UCLASS()
class MAGICMEDIA_TEST_API UVirtualKeyboardUI : public UBaseUI
{
	GENERATED_BODY()


public:
	void NativePreConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* _textResult;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UGridPanel* _keyboardButtons;

	void RightKey();
	void LefttKey();
	void UptKey();
	void DownKey();
	void Select();
	void BackSpace();

private:
	void UnselectAllButtons();
	void SetButtonCollors(SlotState slotState, KeySlot* keySlot);
	void SetSelected(int indexSelected);
	int _indexSelected;
	std::map<int, KeySlot*> _buttons;
	const int COLUNM_COUNT = 9;
	const int LETTERS_COUNT = 27;
	const FString _letters[27]	{ "q", "w", "e", "r", "t", "y", "u", "i", "o",
								  "p", "a", "s", "d", "f", "g", "h", "j", "k",
								  "l", "z", "x", "c", "v", "b", "n", "m", "_" };

	const FLinearColor GetSelectedColor();
	const FLinearColor GetUnselecteColor();

};