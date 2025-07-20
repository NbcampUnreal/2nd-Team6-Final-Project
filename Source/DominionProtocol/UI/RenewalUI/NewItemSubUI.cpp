// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RenewalUI/NewItemSubUI.h"

#include "NewInventoryItemContainer.h"
#include "NewItemFilterContainer.h"
#include "NewItemInfoCard.h"
#include "NewItemSlotContainer.h"

UInputMappingContext* UNewItemSubUI::GetInputMappingContext_Implementation() const
{
	if (!ItemSubUIMappingContext)
	{
		return nullptr;	
	}

	return ItemSubUIMappingContext;
}

void UNewItemSubUI::RefreshWidget()
{
	// ItemSlotContainer->RefreshWidget();
	InventoryItemContainer->RefreshWidget();

	const FGameplayTag ItemTag = InventoryItemContainer->GetClickedItemTag();
	const int32 ItemQuantity = InventoryItemContainer->GetClickedItemQuantity();
	ItemInfoCard->SetInfo(ItemTag, ItemQuantity);
}

void UNewItemSubUI::NativeConstruct()
{
	Super::NativeConstruct();

	OnVisibilityChanged.AddDynamic(this, &UNewItemSubUI::RequestRefreshWidget);
}

void UNewItemSubUI::RequestRefreshWidget(const ESlateVisibility NewVisibility)
{
	if (ESlateVisibility::Visible == NewVisibility)
	{
		RefreshWidget();
	}
}
