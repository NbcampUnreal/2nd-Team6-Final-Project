// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RenewalUI/NewItemFilter.h"

#include "Components/Image.h"

void UNewItemFilter::SetInfo()
{
	Super::SetInfo();

	ItemFilterImage->SetBrushFromTexture(IconTexture);
}

void UNewItemFilter::GetFocus()
{
	Super::GetFocus();

	OnChangeItemFilterFocusEvent.Broadcast(ItemFilter);
	GetFocusEffects();
}

void UNewItemFilter::LoseFocus()
{
	Super::LoseFocus();

	LoseFocusEffects();
}

void UNewItemFilter::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetInfo();
}
