// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RenewalUI/NewInventoryItem.h"

#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/ItemComponent/ItemComponent.h"

void UNewInventoryItem::SetInfo()
{
}

void UNewInventoryItem::SetItemInfo(const FGameplayTag& ItemTag, UTexture2D* ItemTexture, const FString& ItemNameString,
                                const FText& ItemDescription, const int32 CurrentItemQuantity, const int32 MaxItemQuantity,
                                const EItemType ItemType)
{
	ItemData.ItemTag = ItemTag;
	ItemData.ItemIcon = ItemTexture;
	ItemData.ItemName = ItemNameString;
	ItemData.ItemDescription = ItemDescription;
	ItemData.CurrentQuantity = CurrentItemQuantity;
	ItemData.MaxStackQuantity = MaxItemQuantity;
	ItemData.ItemType = ItemType;
	
	if (!ItemTag.IsValid())
	{
		ItemName->SetText(FText::FromString(TEXT("")));
		ItemAmount->SetText(FText::FromString(TEXT("")));
		return;
	}
	
	ItemIcon->SetBrushFromTexture(ItemTexture);
	ItemName->SetText(FText::FromString(ItemNameString));
	ItemAmount->SetText(FText::FromString(FString::Printf(TEXT("%d / %d"), CurrentItemQuantity, MaxItemQuantity)));

	DisplayInfo();
}

void UNewInventoryItem::GetFocus()
{
	Super::GetFocus();

	GetFocusEffects();
	
	OnChangeInventoryItemFocusEvent.Broadcast(ItemData.ItemTag, ItemData.CurrentQuantity);
}

void UNewInventoryItem::LoseFocus()
{
	Super::LoseFocus();

	LoseFocusEffects();
}

void UNewInventoryItem::BroadcastButtonClickEvent() const
{
	OnInventoryItemButtonClickedEvent.Broadcast();
}

void UNewInventoryItem::DisplayInfo()
{
	// 1. 아이템이 존재 하는지 확인
	if (!ItemData.ItemTag.IsValid())
	{
		ItemIcon->SetVisibility(ESlateVisibility::Hidden);
		return;
	}
	
	ItemIcon->SetVisibility(ESlateVisibility::Visible);

	// 2. 장착됨 표시 확인 
	bIsEquippedItem = false;
	
	for (const TPair<FName, FGameplayTag> Pair : TotalItemSlotMap)
	{
		if (ItemData.ItemTag == Pair.Value)
		{
			bIsEquippedItem = true;		
			EquipItemEffect->SetVisibility(ESlateVisibility::Visible);
		}
	}

	if (!bIsEquippedItem)
	{
		EquipItemEffect->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UNewInventoryItem::NativeConstruct()
{
	Super::NativeConstruct();

	// 장착됨 표시를 위한 변수 설정
	APawn* PlayerPawn = GetOwningPlayerPawn();
	if (PlayerPawn)
	{
		const auto* ItemComponent = PlayerPawn->GetComponentByClass<UItemComponent>();
		if (ItemComponent)
		{
			const TMap<FName, FGameplayTag> EquipmentSlotMap = ItemComponent->GetEquipmentSlots();
			const TMap<FName, FGameplayTag> ConsumableSlotMap = ItemComponent->GetConsumableSlots();

			TotalItemSlotMap.Empty();
			TotalItemSlotMap.Append(EquipmentSlotMap);
			TotalItemSlotMap.Append(ConsumableSlotMap);
		}
	}
}
