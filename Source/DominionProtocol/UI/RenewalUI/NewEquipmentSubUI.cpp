// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RenewalUI/NewEquipmentSubUI.h"

#include "Components/ItemComponent/ItemComponent.h"
#include "Components/StatusComponent/StatusComponent.h"

void UNewEquipmentSubUI::NativeConstruct()
{
	Super::NativeConstruct();

	auto* PlayerStatusComponent = GetOwningPlayerPawn()->FindComponentByClass<UStatusComponent>();
	if (PlayerStatusComponent)
	{
		StatusComponent = PlayerStatusComponent;
	}

	auto* PlayerItemComponent = GetOwningPlayerPawn()->FindComponentByClass<UItemComponent>();
	if (PlayerItemComponent)
	{
		ItemComponent = PlayerItemComponent;
		BindEquippedSlotsDelegates();
	}
}

void UNewEquipmentSubUI::BindEquippedSlotsDelegates()
{
	if (ItemComponent)
	{
		ItemComponent->OnInventoryEquippedSlotItemsChanged.AddUObject(this, &UNewEquipmentSubUI::OnUpdateEquippedSlots);
		ItemComponent->OnInventoryConsumableSlotItemsChanged.AddUObject(this, &UNewEquipmentSubUI::OnUpdateEquippedSlots);
	}

	
}

void UNewEquipmentSubUI::OnUpdateEquippedSlots()
{
	UpdateEquippedSlots();
}
