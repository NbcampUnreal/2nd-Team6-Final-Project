// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RenewalUI/NewInventoryItemContainer.h"

#include "NewEquipmentSubUI.h"
#include "NewInventoryItem.h"
#include "Components/ItemComponent/ItemComponent.h"
#include "Player/InGameController.h"

void UNewInventoryItemContainer::NativeConstruct()
{
	Super::NativeConstruct();

	BindInputActionsDelegates();
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

void UNewInventoryItemContainer::BindChangeItemFilterFocusDelegates()
{
	
}

void UNewInventoryItemContainer::SetDisplayItemFilter(const EDisplayItemFilter NewDisplayItemFilter)
{
	DisplayItemFilter = NewDisplayItemFilter;
}

void UNewInventoryItemContainer::SetClickedItemTag(const FGameplayTag NewClickedItemTag)
{
	ClickedItemTag = NewClickedItemTag;
}

void UNewInventoryItemContainer::SetClickedItemQuantity(const int32 NewClickedItemQuantity)
{
	ClickedItemQuantity = NewClickedItemQuantity;
}

void UNewInventoryItemContainer::ChangeFocusIndex(const int32 NewFocusIndex)
{
	Super::ChangeFocusIndex(NewFocusIndex);

	SetDisplayFocusIndex(NewFocusIndex);
}

void UNewInventoryItemContainer::RefreshWidget()
{
	SetCurrentItemDataArray();
	SetContentInfo();
	SetFocusIndex();
}

void UNewInventoryItemContainer::SetDisplayFocusIndex(const int32 NewFocusIndex)
{
	switch (DisplayItemFilter)
	{
	case EDisplayItemFilter::AllItems :
		{
			AllItemsFocusIndex = NewFocusIndex;
		}
	case EDisplayItemFilter::AccessoryItems :
		{
			AccessoryItemsFocusIndex = NewFocusIndex;
		}
	case EDisplayItemFilter::ConsumableItems :
		{
			ConsumableItemsFocusIndex = NewFocusIndex;
		}
	case EDisplayItemFilter::OtherItems :
		{
			OtherItemsFocusIndex = NewFocusIndex;
		}
	case EDisplayItemFilter::SkillItems :
		{
			SkillItemsFocusIndex = NewFocusIndex;
		}
	case EDisplayItemFilter::WeaponItems :
		{
			WeaponItemsFocusIndex = NewFocusIndex;
		}
	}
}

void UNewInventoryItemContainer::SetContentInfo()
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
		switch (DisplayItemFilter)
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
	switch (DisplayItemFilter)
	{
	case EDisplayItemFilter::AllItems :
		{
			ChangeFocusIndex(AllItemsFocusIndex);
		}
	case EDisplayItemFilter::AccessoryItems :
		{
			ChangeFocusIndex(AccessoryItemsFocusIndex);
		}
	case EDisplayItemFilter::ConsumableItems :
		{
			ChangeFocusIndex(ConsumableItemsFocusIndex);
		}
	case EDisplayItemFilter::OtherItems :
		{
			ChangeFocusIndex(OtherItemsFocusIndex);
		}
	case EDisplayItemFilter::SkillItems :
		{
			ChangeFocusIndex(SkillItemsFocusIndex);
		}
	case EDisplayItemFilter::WeaponItems :
		{
			ChangeFocusIndex(WeaponItemsFocusIndex);
		}
	}
}
