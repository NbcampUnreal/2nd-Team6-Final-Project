// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RenewalUI/NewEquipmentSubUI.h"

#include "NewInventoryItemContainer.h"
#include "NewItemSlot.h"
#include "NewItemSlotContainer.h"
#include "Components/Border.h"
#include "Components/ItemComponent/ItemComponent.h"
#include "Components/StatusComponent/StatusComponent.h"

UInputMappingContext* UNewEquipmentSubUI::GetInputMappingContext_Implementation() const
{
	if (!EquipmentSubUIMappingContext)
	{
		return nullptr;	
	}
	
	return EquipmentSubUIMappingContext;
}

void UNewEquipmentSubUI::RefreshEquipmentSubUI()
{
	
}

void UNewEquipmentSubUI::ShowInventoryItemContainer(const FName SlotName, const EDisplayItemFilter DisplayFilter) const
{
	InventoryBorder->SetVisibility(ESlateVisibility::Visible);

	InventoryItemContainer->SetLastDisplayArray(DisplayFilter);
	InventoryItemContainer->SetClickedSlotName(SlotName);
}

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

	BindSlotClickedDelegates();
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

void UNewEquipmentSubUI::BindSlotClickedDelegates()
{
	TArray<UNewItemSlot*> SlotArray = EquippedSlotContainer->GetSlotWidgetArray();
	if (SlotArray.Num() > 0)
	{
		for (UNewItemSlot* ItemSlot : SlotArray)
		{
			ItemSlot->OnItemSlotClickedEvent.AddUObject(this, &UNewEquipmentSubUI::ShowInventoryItemContainer);	
		}
	}
}
