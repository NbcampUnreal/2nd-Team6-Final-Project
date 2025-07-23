// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RenewalUI/NewItemSubUI.h"

#include "NewInventoryItem.h"
#include "NewInventoryItemContainer.h"
#include "NewItemFilter.h"
#include "NewItemFilterContainer.h"
#include "NewItemInfoCard.h"
#include "Components/TextBlock.h"
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
	InventoryItemContainer->RefreshWidget(CurrentItemFilter);
	ItemInfoCard->SetInfo(FocusItemTag, FocusItemQuantity);
	SetupItemTypeName();
}

void UNewItemSubUI::SetupItemTypeName()
{
	const UEnum* EnumPtr = StaticEnum<EDisplayItemFilter>();
	if (EnumPtr)
	{
		const FText EnumDisplayName = EnumPtr->GetDisplayNameTextByValue(static_cast<int32>(CurrentItemFilter));
		ItemTypeName->SetText(EnumDisplayName);
	}
}

void UNewItemSubUI::SequenceChangeItemFilterEvent(const EDisplayItemFilter NewItemFilter)
{
	InventoryItemContainer->SaveFocusIndex(CurrentItemFilter);	
	SetCurrentItemFilter(NewItemFilter);
	RefreshWidget();
}

void UNewItemSubUI::SequenceChangeFocusItemEvent(const FGameplayTag NewItemTag, const int32 NewItemQuantity)
{
	SetFocusItemTag(NewItemTag);
	SetFocusItemQuantity(NewItemQuantity);
	ItemInfoCard->SetInfo(FocusItemTag, FocusItemQuantity);
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
			ItemFilter->OnChangeItemFilterFocusEvent.AddUObject(this, &UNewItemSubUI::SequenceChangeItemFilterEvent);
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
			InventoryItem->OnChangeInventoryItemFocusEvent.AddUObject(this, &UNewItemSubUI::SequenceChangeFocusItemEvent);
		}
	}
}
