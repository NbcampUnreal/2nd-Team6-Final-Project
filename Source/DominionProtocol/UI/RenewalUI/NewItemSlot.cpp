// Fill out your copyright notice in the Description page of Project Settings.


#include "NewItemSlot.h"

#include "Components/SizeBox.h"
#include "Components/ItemComponent/ItemComponent.h"

bool UNewItemSlot::SearchingSlotItem()
{
	if (!ItemTag.IsValid())
	{
		if (ItemComponent)
		{
			TMap<FName, FGameplayTag> ConsumableItemSlotMap = ItemComponent->GetConsumableSlots();
			TMap<FName, FGameplayTag> EquipmentSlotMap = ItemComponent->GetEquipmentSlots();
				
			if (ConsumableItemSlotMap.Find(SlotName))
			{
				ItemTag = ConsumableItemSlotMap[SlotName];
			}
			else if (EquipmentSlotMap.Find(SlotName))
			{
				ItemTag = EquipmentSlotMap[SlotName];
			}
		}
	}

	return ItemTag.IsValid();
}

void UNewItemSlot::NativeConstruct()
{
	const APawn* PlayerPawn = GetOwningPlayerPawn();
	if (PlayerPawn)
	{
		ItemComponent = PlayerPawn->GetComponentByClass<UItemComponent>();
	}
	
	Super::NativeConstruct();
}

void UNewItemSlot::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	Sizer->SetWidthOverride(Size.X);
	Sizer->SetHeightOverride(Size.Y);
}
