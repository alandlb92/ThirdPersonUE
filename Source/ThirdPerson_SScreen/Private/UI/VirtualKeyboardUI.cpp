// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/VirtualKeyboardUI.h"
#include "Components/BorderSlot.h"
#include "Components/ScaleBoxSlot.h"
#include "Components/GridSlot.h"
#include "Blueprint/WidgetTree.h"
#include "Components/ScaleBox.h"
#include "Components/Border.h"

void UVirtualKeyboardUI::NativePreConstruct()
{
	Super::NativePreConstruct();
	_buttons.Empty();
	for (int i = 0; i < LETTERS_COUNT; i++)
	{
		FString borderName = FString("Border");
		borderName.Append(FString::FromInt(i));

		UBorder* border = WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass(), FName(*borderName));
		UGridSlot* btnSlot = _keyboardButtons->AddChildToGrid(border);
		btnSlot->SetRow(int(i / COLUNM_COUNT));
		btnSlot->SetColumn(i - (btnSlot->Row * COLUNM_COUNT));
		btnSlot->SetPadding(5);
		_keyboardButtons->SetColumnFill(btnSlot->Column, 1);
		_keyboardButtons->SetRowFill(btnSlot->Row, 1);


		UScaleBox* scaleBox = WidgetTree->ConstructWidget<UScaleBox>(UScaleBox::StaticClass(), FName("Scale"));
		UBorderSlot* scaleSlot = Cast<UBorderSlot>(border->AddChild(scaleBox));
		scaleSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
		scaleSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);

		FString TextName = FString("Text");
		TextName.Append(FString::FromInt(i));


		URichTextBlock* text = WidgetTree->ConstructWidget<URichTextBlock>(URichTextBlock::StaticClass(), FName(*TextName));
		text->SetTextStyleSet(TextStyle);
		UScaleBoxSlot* textSlot = Cast<UScaleBoxSlot>(scaleBox->AddChild(text));

		textSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
		textSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
		text->SetText(FText::FromString(_letters[i]));
		text->SetJustification(ETextJustify::Center);

		_buttons.Add(i, FKeySlot(_letters[i], border, text));
	}

	SetSelected(0);
}

FString UVirtualKeyboardUI::GetText()
{
	return _textResult->GetText().ToString();
}

void UVirtualKeyboardUI::SetSelected(int indexSelected)
{
	UnselectAllButtons();

	if (indexSelected >= 0 && indexSelected < LETTERS_COUNT)
	{
		SetButtonCollors(SlotState::SELECTED, _buttons[indexSelected]);
	}

	_indexSelected = indexSelected;
}

void UVirtualKeyboardUI::UnselectAllButtons()
{
	for (int i = 0; i < LETTERS_COUNT; i++)
	{
		if (_buttons.Contains(i))
			SetButtonCollors(SlotState::NOT_SELECTED, _buttons[i]);
	}
}

void UVirtualKeyboardUI::SetButtonCollors(SlotState slotState, FKeySlot keySlot)
{
	if (slotState == SlotState::SELECTED)
	{
		if (keySlot._border)
			keySlot._border->SetBrushColor(borderSelectedColor);
		FString keyE = FString("<KeyboardEnable>");
		keyE.Append(keySlot._character);
		keyE.Append("</>");
		/*if (keySlot._text)
			keySlot._text->SetText(FText::FromString(keyE));*/
	}
	else if (slotState == SlotState::NOT_SELECTED)
	{
		if (keySlot._border)
			keySlot._border->SetBrushColor(borderUnselectedColor);
		FString keyD = FString("<KeyboardDisable>");
		keyD.Append(keySlot._character);
		keyD.Append("</>");
		/*if (keySlot._text)
			keySlot._text->SetText(FText::FromString(keyD));*/
	}
}

void UVirtualKeyboardUI::RightKey()
{
	int mult = int(_indexSelected / COLUNM_COUNT) + 1;
	int maxColunNumber = (mult * COLUNM_COUNT) - 1;
	int minColunNumber = maxColunNumber - COLUNM_COUNT + 1;

	int nextKey = ++_indexSelected;
	if (nextKey > maxColunNumber)
		nextKey = minColunNumber;

	SetSelected(nextKey);
}

void UVirtualKeyboardUI::LefttKey()
{

	int mult = int(_indexSelected / COLUNM_COUNT) + 1;
	int maxColunNumber = (mult * COLUNM_COUNT) - 1;
	int minColunNumber = maxColunNumber - COLUNM_COUNT + 1;

	int nextKey = --_indexSelected;
	if (nextKey < minColunNumber)
		nextKey = maxColunNumber;

	SetSelected(nextKey);
}

void UVirtualKeyboardUI::UpKey()
{
	int lastColun = int((LETTERS_COUNT - 1) / COLUNM_COUNT);
	int nextKey = _indexSelected - COLUNM_COUNT;


	UE_LOG(LogTemp, Warning, TEXT("last colun: %i, Next key: %i"), lastColun, nextKey);

	if (nextKey < 0)
		nextKey += (COLUNM_COUNT * (lastColun + 1));

	SetSelected(nextKey);
}

void UVirtualKeyboardUI::DownKey()
{
	int lastColun = int((LETTERS_COUNT - 1) / COLUNM_COUNT);
	int nextKey = _indexSelected + COLUNM_COUNT;
	int nextColun = (int)(nextKey / COLUNM_COUNT);

	if (nextColun > lastColun)
		nextKey -= (COLUNM_COUNT * (lastColun + 1));

	SetSelected(nextKey);
}

void UVirtualKeyboardUI::Select()
{
	FString result = _textResult->GetText().ToString();
	result.Append(_letters[_indexSelected]);
	_textResult->SetText(FText::FromString(result));
}

void UVirtualKeyboardUI::BackSpace()
{
	FString result = _textResult->GetText().ToString();
	result.RemoveAt(result.Len() - 1);
	_textResult->SetText(FText::FromString(result));
}