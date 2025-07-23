// Fill out your copyright notice in the Description page of Project Settings.


#include "NewItemSlot.h"

#include "Components/Border.h"
#include "Components/SizeBox.h"

void UNewItemSlot::SetInfo()
{
	Super::SetInfo();
}

void UNewItemSlot::BroadcastButtonClickEvent() const
{
	OnItemSlotClickedEvent.Broadcast(SlotItemFilter);
}

void UNewItemSlot::GetFocus()
{
	Super::GetFocus();

	OnItemSlotGetFocusEvent.Broadcast(ItemTag, ItemQuantity, SlotName);
}

void UNewItemSlot::SetInfo(const FGameplayTag NewItemTag, UTexture2D* NewItemIcon, const int32 NewItemQuantity)
{
	ItemTag = NewItemTag;
	ItemQuantity = NewItemQuantity;
	ItemImage->SetBrushFromTexture(NewItemIcon);
}

void UNewItemSlot::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	Sizer->SetWidthOverride(Size.X);
	Sizer->SetHeightOverride(Size.Y);
}
