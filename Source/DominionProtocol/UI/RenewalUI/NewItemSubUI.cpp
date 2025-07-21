// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RenewalUI/NewItemSubUI.h"

#include "NewInventoryItemContainer.h"
#include "NewItemFilterContainer.h"
#include "NewItemInfoCard.h"
#include "Player/InGameController.h"

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
	const FGameplayTag ItemTag = InventoryItemContainer->GetClickedItemTag();
	const int32 ItemQuantity = InventoryItemContainer->GetClickedItemQuantity();
	ItemInfoCard->SetInfo(ItemTag, ItemQuantity);
}

void UNewItemSubUI::NativeConstruct()
{
	Super::NativeConstruct();

	BindInputActionDelegates();
	BindItemFilterChangedDelegates();

	OnVisibilityChanged.AddDynamic(this, &UNewItemSubUI::RequestRefreshWidget);
}

void UNewItemSubUI::RequestRefreshWidget(const ESlateVisibility NewVisibility)
{
	if (ESlateVisibility::Visible == NewVisibility)
	{
		RefreshWidget();
	}
}

void UNewItemSubUI::BindInputActionDelegates()
{
	auto* InGameController = Cast<AInGameController>(GetOwningPlayer());
	if (InGameController)
	{
		InGameController->OnItemUIMoveSelectionLeftEvent.AddUObject(ItemFilterContainer, &UNewItemFilterContainer::DecreaseFocusIndex);
		InGameController->OnItemUIMoveSelectionRightEvent.AddUObject(ItemFilterContainer, &UNewItemFilterContainer::IncreaseFocusIndex);

		InGameController->OnItemUIMoveSelectionUpEvent.AddUObject(InventoryItemContainer, &UNewInventoryItemContainer::DecreaseFocusIndex);
		InGameController->OnItemUIMoveSelectionDownEvent.AddUObject(InventoryItemContainer, &UNewInventoryItemContainer::IncreaseFocusIndex);
	}
}

void UNewItemSubUI::BindItemFilterChangedDelegates()
{
	ItemFilterContainer->OnCurrentItemFilterChangedEvent.AddUObject(InventoryItemContainer, &UNewInventoryItemContainer::SetDisplayItemFilter);
}
