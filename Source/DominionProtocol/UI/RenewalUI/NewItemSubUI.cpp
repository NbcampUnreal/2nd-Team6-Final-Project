// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RenewalUI/NewItemSubUI.h"

#include "NewInventoryItem.h"
#include "NewInventoryItemContainer.h"
#include "NewItemFilter.h"
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

void UNewItemSubUI::RefreshWidget() const 
{
	InventoryItemContainer->RefreshWidget(CurrentItemFilter);
	ItemInfoCard->SetInfo(FocusItemTag, FocusItemQuantity);
}

void UNewItemSubUI::SetFocusItemInfo(const FGameplayTag NewItemTag, const int32 NewItemQuantity)
{
	FocusItemTag = NewItemTag;
	FocusItemQuantity = NewItemQuantity;

	ItemInfoCard->SetInfo(FocusItemTag, FocusItemQuantity);
}

void UNewItemSubUI::SetCurrentItemFilter(const EDisplayItemFilter NewItemFilter)
{
	CurrentItemFilter = NewItemFilter;

	RefreshWidget();
}

void UNewItemSubUI::NativeConstruct()
{
	Super::NativeConstruct();

	BindInputActionDelegates();
	BindItemFilterChangedDelegates();
	BindFocusItemChangedDelegates();

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
	const TArray<UBaseContent*> ContentArray = ItemFilterContainer->GetContentArray();
	if (ContentArray.Num() > 0)
	{
		for (UBaseContent* Content : ContentArray)
		{
			auto* ItemFilter = Cast<UNewItemFilter>(Content);
			ItemFilter->OnChangeItemFilterFocusEvent.AddUObject(this, &UNewItemSubUI::SetCurrentItemFilter);
		}
	}
}

void UNewItemSubUI::BindFocusItemChangedDelegates()
{
	const TArray<UBaseContent*> ContentArray = InventoryItemContainer->GetContentArray();
	if (ContentArray.Num() > 0)
	{
		for (UBaseContent* Content : ContentArray)
		{
			auto* InventoryItem = Cast<UNewInventoryItem>(Content);
			InventoryItem->OnChangeInventoryItemFocusEvent.AddUObject(this, &UNewItemSubUI::SetFocusItemInfo);
		}
	}
}
