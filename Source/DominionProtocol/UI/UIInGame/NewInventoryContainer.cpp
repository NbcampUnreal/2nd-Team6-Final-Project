// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIInGame/NewInventoryContainer.h"

#include "Components/ItemComponent/ItemComponent.h"

void UNewInventoryContainer::NativeConstruct()
{
	Super::NativeConstruct();

	BindInventoryDelegates();
}

void UNewInventoryContainer::BindInventoryDelegates()
{
	AActor* PlayerCharacter = GetOwningPlayerPawn();
	if (PlayerCharacter)
	{
		ItemComponent = PlayerCharacter->GetComponentByClass<UItemComponent>();
		if (ItemComponent)
		{
			ItemComponent->OnInventoryItemListChanged.AddUObject(this, &UNewInventoryContainer::OnUpdateInventoryItemList);
		}
	}
}

void UNewInventoryContainer::OnUpdateInventoryItemList()
{
	InventoryAllItems = ItemComponent->GetInventoryDisplayItems();
	
	TArray<FItemUISlotData> TempEquippableItemsArray;
	TArray<FItemUISlotData> TempConsumableItemsArray;
	TArray<FItemUISlotData> TempOtherItemsArray;
		
	for (FItemUISlotData& SlotData : InventoryAllItems)
	{

		
		if (SlotData.ItemTag.MatchesTag(ItemTags::EquippableItem))
		{
			TempEquippableItemsArray.Add(SlotData);
			continue;
		}

		if (SlotData.ItemTag.MatchesTag(ItemTags::ConsumableItem))
		{
			TempConsumableItemsArray.Add(SlotData);
			continue;
		}
		
		if (SlotData.ItemTag.MatchesTag(ItemTags::OtherItem))
    	{
			TempOtherItemsArray.Add(SlotData);
			continue;
		}

		ensureMsgf(false, TEXT("%s:: Error Item Tag"), *SlotData.ItemName);
	}

	EquippableItemsArray = TempEquippableItemsArray;
	ConsumableItemsArray = TempConsumableItemsArray;
	OtherItemsArray = TempOtherItemsArray;

	UpdateInventoryItemList();
}