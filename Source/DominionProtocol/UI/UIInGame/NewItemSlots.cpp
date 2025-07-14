// Fill out your copyright notice in the Description page of Project Settings.


#include "NewItemSlots.h"

#include "Components/ItemComponent/ItemComponent.h"

void UNewItemSlots::NativeConstruct()
{
	Super::NativeConstruct();

	BindItemSlotsDelegate();
}

void UNewItemSlots::BindItemSlotsDelegate()
{
	AActor* PlayerCharacter = GetOwningPlayerPawn();
	if (PlayerCharacter)
	{
		ItemComponent = PlayerCharacter->GetComponentByClass<UItemComponent>();
		if (ItemComponent)
		{
			ItemComponent->OnInventoryEquippedSlotItemsChanged.AddUObject(this, &UNewItemSlots::OnUpdateEquippableSlotItems);
			ItemComponent->OnInventoryConsumableSlotItemsChanged.AddUObject(this, &UNewItemSlots::OnUpdateConsumableSlotItems);
		}
	}
}

void UNewItemSlots::OnUpdateEquippableSlotItems()
{
	InventoryEquippableSlotItems = ItemComponent->GetEquippedDisplayItems();

	UpdateEquippableSlotItems();
}

void UNewItemSlots::OnUpdateConsumableSlotItems()
{
	InventoryConsumableSlotItems = ItemComponent->GetConsumableDisplayItems();

	UpdateConsumableSlotItems();
}
