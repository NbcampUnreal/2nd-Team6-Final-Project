// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RenewalUI/NewInventoryItemContainer.h"

#include "NewInventoryItem.h"
#include "Components/PanelWidget.h"
#include "Components/ItemComponent/ItemComponent.h"
#include "Player/InGameController.h"

void UNewInventoryItemContainer::NativeConstruct()
{
	Super::NativeConstruct();

	BindInventoryRefreshDelegates();
	SetInventoryItemOwningWidget();
}

void UNewInventoryItemContainer::SetInventoryItemOwningWidget()
{
	const TArray<UWidget*> ItemArray = ContentContainer->GetAllChildren();
	if (ItemArray.Num() > 0)
	{
		for (UWidget* Content : ItemArray)
		{
			auto* InventoryItem = Cast<UNewInventoryItem>(Content);
			if (InventoryItem)
			{
				InventoryItem->SetOwningWidget(this);
			}
		}
	}
}

void UNewInventoryItemContainer::BindInventoryRefreshDelegates()
{
	const APawn* PlayerCharacter = GetOwningPlayerPawn();
	if (PlayerCharacter)
	{
		ItemComponent = PlayerCharacter->GetComponentByClass<UItemComponent>();
		if (ItemComponent)
		{
			ItemComponent->OnInventoryItemListChanged.AddUObject(this, &UNewInventoryItemContainer::RefreshInventoryItemInfo);
		}
	}

	OnLastDisplayArrayChangedEvent.AddUObject(this, &UNewInventoryItemContainer::RefreshInventoryItemInfo);
}

void UNewInventoryItemContainer::BindInputActionsDelegates()
{
	auto* InGameController = Cast<AInGameController>(GetOwningPlayer());
	if (InGameController)
	{
		InGameController->OnItemUIMoveSelectionUpEvent.AddUObject(this, &UNewInventoryItemContainer::DecreaseFocusIndex);
		InGameController->OnItemUIMoveSelectionDownEvent.AddUObject(this, &UNewInventoryItemContainer::IncreaseFocusIndex);
	}
}

void UNewInventoryItemContainer::SetLastDisplayArray(const EDisplayItemFilter& NewItemDisplay)
{
	LastDisplayArray = NewItemDisplay;
	OnLastDisplayArrayChangedEvent.Broadcast();
}

void UNewInventoryItemContainer::ChangeFocusIndex(const int32 NewFocusIndex)
{
	Super::ChangeFocusIndex(NewFocusIndex);

	SetDisplayFocusIndex(NewFocusIndex);
}

void UNewInventoryItemContainer::RefreshInventoryItemInfo()
{
	SetCurrentItemDataArray();
	SetInventoryItemInfo();
	SetFocusIndex();
}

void UNewInventoryItemContainer::SetDisplayFocusIndex(const int32 NewFocusIndex)
{
	switch (LastDisplayArray)
	{
	case EDisplayItemFilter::AllItems :
		{
			AllItemsIndex = NewFocusIndex;
		}
	case EDisplayItemFilter::AccessoryItems :
		{
			AccessoryItemsIndex = NewFocusIndex;
		}
	case EDisplayItemFilter::ConsumableItems :
		{
			ConsumableItemsIndex = NewFocusIndex;
		}
	case EDisplayItemFilter::OtherItems :
		{
			OtherItemsIndex = NewFocusIndex;
		}
	case EDisplayItemFilter::SkillItems :
		{
			SkillItemsIndex = NewFocusIndex;
		}
	case EDisplayItemFilter::WeaponItems :
		{
			WeaponItemsIndex = NewFocusIndex;
		}
	}
}

void UNewInventoryItemContainer::SetInventoryItemInfo()
{
	for (int32 i = 0; i < ContentArray.Num(); i++)
	{
		auto* InventoryItem = Cast<UNewInventoryItem>(ContentArray[i]);
		if (InventoryItem)
		{
			if (CurrentItemDataArray.IsValidIndex(i))
			{
				FItemUISlotData Data = CurrentItemDataArray[i];
				InventoryItem->SetInfo(Data.ItemTag, Data.ItemIcon, Data.ItemName, Data.ItemDescription, Data.CurrentQuantity, Data.MaxStackQuantity, Data.ItemType);	
			}
			else
			{
				InventoryItem->SetInfo();
			}
		}
	}
}

void UNewInventoryItemContainer::SetCurrentItemDataArray()
{
	if (!ItemComponent)
	{
		return;
	}

	InventoryAllItemDataArray = ItemComponent->GetInventoryDisplayItems();

	TArray<FItemUISlotData> TempInventoryItemArray;

	for (FItemUISlotData Item : InventoryAllItemDataArray)
	{
		switch (LastDisplayArray)
		{
		case EDisplayItemFilter::AllItems :
			{
				TempInventoryItemArray.Add(Item);
			}
		case EDisplayItemFilter::AccessoryItems :
			{
				if (Item.ItemTag.MatchesTag(ItemTags::AccessoryItem))
				{
					TempInventoryItemArray.Add(Item);
				}
			}
		case EDisplayItemFilter::ConsumableItems :
			{
				if (Item.ItemTag.MatchesTag(ItemTags::ConsumableItem))
				{
					TempInventoryItemArray.Add(Item);
				}
			}
		case EDisplayItemFilter::WeaponItems :
			{
				if (Item.ItemTag.MatchesTag(ItemTags::WeaponItem))
				{
					TempInventoryItemArray.Add(Item);
				}
			}
		case EDisplayItemFilter::SkillItems :
			{
				if (Item.ItemTag.MatchesTag(ItemTags::SkillItem))
				{
					TempInventoryItemArray.Add(Item);
				}
			}
		case EDisplayItemFilter::OtherItems :
			{
				if (Item.ItemTag.MatchesTag(ItemTags::OtherItem))
				{
					TempInventoryItemArray.Add(Item);
				}
			}
		default :
			{
				TempInventoryItemArray.Add(Item);
			}
		}
	}
	CurrentItemDataArray = TempInventoryItemArray;
}

void UNewInventoryItemContainer::SetFocusIndex()
{
	switch (LastDisplayArray)
	{
	case EDisplayItemFilter::AllItems :
		{
			ChangeFocusIndex(AllItemsIndex);
		}
	case EDisplayItemFilter::AccessoryItems :
		{
			ChangeFocusIndex(AccessoryItemsIndex);
		}
	case EDisplayItemFilter::ConsumableItems :
		{
			ChangeFocusIndex(ConsumableItemsIndex);
		}
	case EDisplayItemFilter::OtherItems :
		{
			ChangeFocusIndex(OtherItemsIndex);
		}
	case EDisplayItemFilter::SkillItems :
		{
			ChangeFocusIndex(SkillItemsIndex);
		}
	case EDisplayItemFilter::WeaponItems :
		{
			ChangeFocusIndex(WeaponItemsIndex);
		}
	}
}
