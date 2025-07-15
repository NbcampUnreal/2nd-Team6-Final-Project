// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RenewalUI/NewItemFilterIcon.h"

#include "Components/Image.h"

void UNewItemFilterIcon::SetInfo()
{
	Super::SetInfo();

	ItemFilterImage->SetBrushFromTexture(IconTexture);
}

void UNewItemFilterIcon::GetFocus()
{
	Super::GetFocus();

	GetFocusEffects();
}

void UNewItemFilterIcon::LoseFocus()
{
	Super::LoseFocus();

	LoseFocusEffects();
}

void UNewItemFilterIcon::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetInfo();
}
