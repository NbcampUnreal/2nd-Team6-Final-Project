// Fill out your copyright notice in the Description page of Project Settings.


#include "NewItemSlotDisplay.h"

#include "Components/ItemComponent/ItemComponent.h"

void UNewItemSlotDisplay::NativeConstruct()
{
	Super::NativeConstruct();

	BindItemSlotsDelegate();
}

void UNewItemSlotDisplay::BindItemSlotsDelegate()
{
	AActor* PlayerCharacter = GetOwningPlayerPawn();
	if (PlayerCharacter)
	{
		ItemComponent = PlayerCharacter->GetComponentByClass<UItemComponent>();
		if (ItemComponent)
		{
			ItemComponent->OnInventoryEquippedSlotItemsChanged.AddUObject(this, &UNewItemSlotDisplay::OnUpdateEquippableSlotItems);
			ItemComponent->OnInventoryConsumableSlotItemsChanged.AddUObject(this, &UNewItemSlotDisplay::OnUpdateConsumableSlotItems);
		}
	}
}

void UNewItemSlotDisplay::OnUpdateEquippableSlotItems()
{
	InventoryEquippableSlotItems = ItemComponent->GetEquippedDisplayItems();

	UpdateEquippableSlotItems();
}

void UNewItemSlotDisplay::OnUpdateConsumableSlotItems()
{
	InventoryConsumableSlotItems = ItemComponent->GetConsumableDisplayItems();

	UpdateConsumableSlotItems();
}
