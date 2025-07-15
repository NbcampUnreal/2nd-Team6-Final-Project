// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RenewalUI/NewShotcutButton.h"

#include "Components/SizeBox.h"
#include "Components/TextBlock.h"

void UNewShotcutButton::SetShotcutKeyText(const FText& NewShotcutKeyText)
{
	ShotcutKeyText = NewShotcutKeyText;
}

void UNewShotcutButton::SetShotcutScriptText(const FText& NewShotcutScriptText)
{
	ShotcutScriptText = NewShotcutScriptText;
}

void UNewShotcutButton::SetInfo()
{
	Sizer->SetWidthOverride(Size.X);
	Sizer->SetHeightOverride(Size.Y);
	
	ShotcutKey->SetText(ShotcutKeyText);
	ShotcutScript->SetText(ShotcutScriptText);

	DisplayInfo();
}

void UNewShotcutButton::DisplayInfo()
{
	if (ShotcutKeyText.IsEmpty() && ShotcutScriptText.IsEmpty())
	{
		SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		SetVisibility(ESlateVisibility::Visible);
	}
	
	if (ShotcutKeyText.IsEmpty())
	{
		ShotcutKey->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		ShotcutKey->SetVisibility(ESlateVisibility::Visible);
	}

	if (ShotcutScriptText.IsEmpty())
	{
		ShotcutScript->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		ShotcutScript->SetVisibility(ESlateVisibility::Visible);
	}
}

void UNewShotcutButton::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetInfo();
}
