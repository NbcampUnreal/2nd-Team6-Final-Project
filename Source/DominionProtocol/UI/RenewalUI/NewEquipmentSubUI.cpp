// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RenewalUI/NewEquipmentSubUI.h"

#include "NewInventoryItemContainer.h"
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

void UNewEquipmentSubUI::RequestRefreshWidget(const ESlateVisibility NewVisibility)
{
	if (ESlateVisibility::Visible == NewVisibility)
	{
		RefreshWidget();
	}
}

void UNewEquipmentSubUI::RefreshWidget()
{
	ItemSlotContainer->RefreshWidget();
	// InventoryItemContainer->RefreshWidget();
	
	RequestRefreshStatusPlate();
}

void UNewEquipmentSubUI::ShowInventoryItemContainer() const
{
	InventoryBorder->SetVisibility(ESlateVisibility::Visible);
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
	}
	
	BindRefreshWidgetDelegates();

	OnVisibilityChanged.AddDynamic(this, &UNewEquipmentSubUI::RequestRefreshWidget);
}

void UNewEquipmentSubUI::BindRefreshWidgetDelegates()
{
	if (ItemComponent)
	{
		ItemComponent->OnInventoryEquippedSlotItemsChanged.AddUObject(this, &UNewEquipmentSubUI::RefreshWidget);
		ItemComponent->OnInventoryConsumableSlotItemsChanged.AddUObject(this, &UNewEquipmentSubUI::RefreshWidget);
	}
}
