// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RenewalUI/NewEquipmentSubUI.h"

#include "NewInventoryItem.h"
#include "NewInventoryItemContainer.h"
#include "NewItemInfoCard.h"
#include "NewItemSlot.h"
#include "NewItemSlotContainer.h"
#include "NewShotcutButton.h"
#include "Components/Border.h"
#include "Components/ItemComponent/ItemComponent.h"
#include "Components/StatusComponent/StatusComponent.h"
#include "Player/InGameController.h"

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
	InventoryItemContainer->RefreshWidget(ClickedSlotItemFilter);
	
	RequestRefreshStatusPlate();
}

void UNewEquipmentSubUI::IncreaseFocusIndex() const
{
	if (bIsInventoryItemContainerVisible)
	{
		InventoryItemContainer->IncreaseFocusIndex();
	}
	else
	{
		ItemSlotContainer->IncreaseFocusIndex();
	}
}

void UNewEquipmentSubUI::DecreaseFocusIndex() const 
{
	if (bIsInventoryItemContainerVisible)
	{
		InventoryItemContainer->DecreaseFocusIndex();
	}
	else
	{
		ItemSlotContainer->DecreaseFocusIndex();
	}
}

void UNewEquipmentSubUI::SequenceChangeFocusSlotItemEvent(const FGameplayTag NewItemTag, const int32 NewItemQuantity, const FName NewItemSlotName)
{
	SetFocusSlotItemTag(NewItemTag);
	SetFocusSlotItemQuantity(NewItemQuantity);
	SetFocusSlotName(NewItemSlotName);
	ItemInfo->SetInfo(FocusSlotItemTag, FocusSlotItemQuantity);
}

void UNewEquipmentSubUI::SequenceChangeClickedSlotItemEvent(const EDisplayItemFilter NewItemFilter)
{
	SetClickedSlotItemFilter(NewItemFilter);
	RefreshWidget();
	ShowInventoryItemContainer();
}

void UNewEquipmentSubUI::SequenceChangeFocusInventoryItemEvent(const FGameplayTag NewItemTag,const int32 NewItemQuantity)
{
	SetFocusInventoryItemTag(NewItemTag);
	SetFocusInventoryItemQuantity(NewItemQuantity);
	ItemInfo->SetInfo(FocusInventoryItemTag, FocusInventoryItemQuantity);
}

void UNewEquipmentSubUI::SequenceChangeClickedInventoryItemEvent() const
{
	if (FocusSlotItemTag.MatchesTagExact(FocusInventoryItemTag))
	{
		UnequipItemToSlot();
	}
	else
	{
		EquipItemToSlot();
	}
}

void UNewEquipmentSubUI::ShowInventoryItemContainer() 
{
	InventoryBorder->SetVisibility(ESlateVisibility::Visible);
	bIsInventoryItemContainerVisible = true;
}

void UNewEquipmentSubUI::HideInventoryItemContainer() 
{
	InventoryBorder->SetVisibility(ESlateVisibility::Collapsed);
	bIsInventoryItemContainerVisible = false;
}

void UNewEquipmentSubUI::EquipItemToSlot() const 
{
	if (FocusInventoryItemTag.IsValid() && FocusSlotName.IsValid())
	{
		ItemComponent->EquipItem(FocusSlotName, FocusInventoryItemTag);
	}
}

void UNewEquipmentSubUI::UnequipItemToSlot() const
{
	if (FocusSlotItemTag.IsValid() && FocusSlotName.IsValid())
	{
		ItemComponent->UnequipItem(FocusSlotName);
	}
}

void UNewEquipmentSubUI::NativeConstruct()
{
	Super::NativeConstruct();

	// Status 갱신을 위해서 필요
	auto* PlayerStatusComponent = GetOwningPlayerPawn()->FindComponentByClass<UStatusComponent>();
	if (PlayerStatusComponent)
	{
		StatusComponent = PlayerStatusComponent;
	}
	
	auto* PlayerItemComponent = GetOwningPlayerPawn()->FindComponentByClass<UItemComponent>();
	if (PlayerItemComponent)
	{
		ItemComponent = PlayerItemComponent;
		BindUpdateInventorySlotDataDelegates();
	}

	BindFocusItemChangedDelegates();
	BindClickedItemChangedDelegates();
	BindCloseInventoryButtonClickedDelegates();
	BindInputActionDelegates();

	OnVisibilityChanged.AddDynamic(this, &UNewEquipmentSubUI::RequestRefreshWidget);
}

void UNewEquipmentSubUI::BindUpdateInventorySlotDataDelegates()
{
	if (ItemComponent)
	{
		ItemComponent->OnInventoryEquippedSlotItemsChanged.AddUObject(this, &UNewEquipmentSubUI::RefreshWidget);
		ItemComponent->OnInventoryConsumableSlotItemsChanged.AddUObject(this, &UNewEquipmentSubUI::RefreshWidget);
	}
}

void UNewEquipmentSubUI::BindFocusItemChangedDelegates()
{
	if (ItemSlotContainer)
	{
		const TArray<UNewItemSlot*> SlotArray = ItemSlotContainer->GetSlotWidgetArray();
		if (SlotArray.Num() > 0)
		{
			for (UNewItemSlot* ItemSlot : SlotArray)
			{
				ItemSlot->OnItemSlotGetFocusEvent.AddUObject(this, &UNewEquipmentSubUI::SequenceChangeFocusSlotItemEvent);
			}
		}	
	}

	if (InventoryItemContainer)
	{
		const TArray<UBaseContent*> ContentArray = InventoryItemContainer->GetContentArray();
		if (ContentArray.Num() > 0)
		{
			for (UBaseContent* Content : ContentArray)
			{
				auto* InventoryItem = Cast<UNewInventoryItem>(Content);
				InventoryItem->OnChangeInventoryItemFocusEvent.AddUObject(this, &UNewEquipmentSubUI::SequenceChangeFocusInventoryItemEvent);
			}
		}	
	}
}

void UNewEquipmentSubUI::BindClickedItemChangedDelegates()
{
	if (ItemSlotContainer)
	{
		const TArray<UNewItemSlot*> SlotArray = ItemSlotContainer->GetSlotWidgetArray();
		if (SlotArray.Num() > 0)
		{
			for (UNewItemSlot* ItemSlot : SlotArray)
			{
				ItemSlot->OnItemSlotClickedEvent.AddUObject(this, &UNewEquipmentSubUI::SequenceChangeClickedSlotItemEvent);
			}
		}	
	}

	if (InventoryItemContainer)
	{
		const TArray<UBaseContent*> ContentArray = InventoryItemContainer->GetContentArray();
		if (ContentArray.Num() > 0)
		{
			for (UBaseContent* Content : ContentArray)
			{
				auto* InventoryItem = Cast<UNewInventoryItem>(Content);
				if (InventoryItem)
				{
					InventoryItem->OnInventoryItemButtonClickedEvent.AddUObject(this, &UNewEquipmentSubUI::SequenceChangeClickedInventoryItemEvent);
				}
			}
		}
	}
}

void UNewEquipmentSubUI::BindCloseInventoryButtonClickedDelegates()
{
	CloseInventoryButton->OnShotcutButtonClickedEvent.AddUObject(this, &UNewEquipmentSubUI::HideInventoryItemContainer);
	EquipButton->OnShotcutButtonClickedEvent.AddUObject(this, &UNewEquipmentSubUI::EquipItemToSlot);
	UnequipButton->OnShotcutButtonClickedEvent.AddUObject(this, &UNewEquipmentSubUI::UnequipItemToSlot);
}

void UNewEquipmentSubUI::BindInputActionDelegates()
{
	auto* InGameController = Cast<AInGameController>(GetOwningPlayer());
	if (InGameController)
	{
		InGameController->OnEquipmentUIMoveSelectionUpEvent.AddUObject(this, &UNewEquipmentSubUI::DecreaseFocusIndex);
		InGameController->OnEquipmentUIMoveSelectionDownEvent.AddUObject(this, &UNewEquipmentSubUI::IncreaseFocusIndex);

		InGameController->OnEquipmentUIEquipItemActionEvent.AddUObject(this, &UNewEquipmentSubUI::EquipItemToSlot);
		InGameController->OnEquipmentUIUnequipItemActionEvent.AddUObject(this, &UNewEquipmentSubUI::UnequipItemToSlot);
	}
}
