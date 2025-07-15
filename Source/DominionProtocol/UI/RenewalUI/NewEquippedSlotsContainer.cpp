// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RenewalUI/NewEquippedSlotsContainer.h"

#include "Components/ItemComponent/ItemComponent.h"


void UNewEquippedSlotsContainer::NativeConstruct()
{
	Super::NativeConstruct();

	BindItemSlotsDelegate();

	SlotWidgetArray.AddUnique(AccessorySlot_Primary);
	SlotWidgetArray.AddUnique(AccessorySlot_Secondary);
	SlotWidgetArray.AddUnique(SkillSlot);
	SlotWidgetArray.AddUnique(WeaponSlot_Primary);
	SlotWidgetArray.AddUnique(WeaponSlot_Secondary);
	SlotWidgetArray.AddUnique(ConsumableSlot_Secondary);
	SlotWidgetArray.AddUnique(ConsumableSlot_Tertiary);
}

void UNewEquippedSlotsContainer::BindItemSlotsDelegate()
{
	AActor* PlayerCharacter = GetOwningPlayerPawn();
	if (PlayerCharacter)
	{
		ItemComponent = PlayerCharacter->GetComponentByClass<UItemComponent>();
		if (ItemComponent)
		{
			ItemComponent->OnInventoryEquippedSlotItemsChanged.AddUObject(this, &UNewEquippedSlotsContainer::OnUpdateEquippableSlotItems);
			ItemComponent->OnInventoryConsumableSlotItemsChanged.AddUObject(this, &UNewEquippedSlotsContainer::OnUpdateConsumableSlotItems);
		}
	}
}

void UNewEquippedSlotsContainer::OnUpdateEquippableSlotItems()
{
	EquippableSlotMap = ItemComponent->GetEquippedDisplayItems();

	UpdateEquippableSlotItems();
}

void UNewEquippedSlotsContainer::OnUpdateConsumableSlotItems()
{
	ConsumableSlotMap = ItemComponent->GetConsumableDisplayItems();

	UpdateConsumableSlotItems();
}