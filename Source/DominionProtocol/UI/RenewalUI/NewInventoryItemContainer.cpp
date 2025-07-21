// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RenewalUI/NewInventoryItemContainer.h"

#include "NewEquipmentSubUI.h"
#include "NewInventoryItem.h"
#include "Components/ItemComponent/ItemComponent.h"

void UNewInventoryItemContainer::NativeConstruct()
{
	Super::NativeConstruct();

	OnVisibilityChanged.AddDynamic(this, &UNewInventoryItemContainer::RequestRefreshWidget);
	OnItemFilterChangedEvent.AddUObject(this, &UNewInventoryItemContainer::RefreshWidget);
}

void UNewInventoryItemContainer::SetDisplayItemFilter(const EDisplayItemFilter NewDisplayItemFilter)
{
	DisplayItemFilter = NewDisplayItemFilter;
	OnItemFilterChangedEvent.Broadcast();
}

void UNewInventoryItemContainer::SetClickedItemTag(const FGameplayTag NewClickedItemTag)
{
	ClickedItemTag = NewClickedItemTag;
}

void UNewInventoryItemContainer::SetClickedItemQuantity(const int32 NewClickedItemQuantity)
{
	ClickedItemQuantity = NewClickedItemQuantity;
}

int32 UNewInventoryItemContainer::GetDisplayFocusIndex() const
{
	switch (DisplayItemFilter)
	{
	case EDisplayItemFilter::AllItems :
		{
			return AllItemsFocusIndex;
		}
	case EDisplayItemFilter::WeaponItems :
		{
			return WeaponItemsFocusIndex;
		}
	case EDisplayItemFilter::AccessoryItems :
		{
			return AccessoryItemsFocusIndex;
		}
	case EDisplayItemFilter::ConsumableItems :
		{
			return ConsumableItemsFocusIndex;
		}
	case EDisplayItemFilter::OtherItems :
		{
			return OtherItemsFocusIndex;
		}
	case EDisplayItemFilter::SkillItems :
		{
			return SkillItemsFocusIndex;
		}
	default :
		{
			return CurrentFocusIndex;
		}
	}
}

void UNewInventoryItemContainer::ChangeFocusIndex(const int32 NewFocusIndex)
{
	Super::ChangeFocusIndex(NewFocusIndex);

	SaveFocusIndex();
}

void UNewInventoryItemContainer::RefreshWidget()
{
	SetItemDataArrays();
	SetCurrentDataArray();
	SetContentInfo();

	const int32 NewFocusIndex = GetDisplayFocusIndex();
	SetFocusIndex(NewFocusIndex);
}

void UNewInventoryItemContainer::RequestRefreshWidget(const ESlateVisibility NewVisibility)
{
	if (ESlateVisibility::Visible == NewVisibility)
	{
		RefreshWidget();
	}
}

void UNewInventoryItemContainer::SaveFocusIndex()
{
	switch (DisplayItemFilter)
	{
	case EDisplayItemFilter::AllItems :
		{
			AllItemsFocusIndex = CurrentFocusIndex;
		}
	case EDisplayItemFilter::WeaponItems :
		{
			WeaponItemsFocusIndex = CurrentFocusIndex;
		}
	case EDisplayItemFilter::AccessoryItems :
		{
			AccessoryItemsFocusIndex = CurrentFocusIndex;
		}
	case EDisplayItemFilter::ConsumableItems :
		{
			ConsumableItemsFocusIndex = CurrentFocusIndex;
		}
	case EDisplayItemFilter::OtherItems :
		{
			OtherItemsFocusIndex = CurrentFocusIndex;
		}
	case EDisplayItemFilter::SkillItems :
		{
			SkillItemsFocusIndex = CurrentFocusIndex;
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
				InventoryItem->SetItemInfo(Data.ItemTag, Data.ItemIcon, Data.ItemName, Data.ItemDescription, Data.CurrentQuantity, Data.MaxStackQuantity, Data.ItemType);	
			}
			else
			{
				InventoryItem->SetItemInfo();
			}
		}
	}
}

void UNewInventoryItemContainer::SetItemDataArrays()
{
	if (!ItemComponent)
	{
		return;
	}

	InventoryAllItemDataArray = ItemComponent->GetInventoryDisplayItems();

	TArray<FItemUISlotData> TempWeaponItemDataArray;
	TArray<FItemUISlotData> TempAccessoryItemDataArray;
	TArray<FItemUISlotData> TempConsumableItemDataArray;
	TArray<FItemUISlotData> TempSkillItemDataArray;
	TArray<FItemUISlotData> TempOtherItemDataArray;

	for (FItemUISlotData ItemData : InventoryAllItemDataArray)
	{
		if (ItemData.ItemTag.IsValid())
		{
			if (ItemData.ItemTag.MatchesTag(ItemTags::WeaponItem))
			{
				TempWeaponItemDataArray.Add(ItemData);
			}

			if (ItemData.ItemTag.MatchesTag(ItemTags::AccessoryItem))
			{
				TempAccessoryItemDataArray.Add(ItemData);
			}

			if (ItemData.ItemTag.MatchesTag(ItemTags::ConsumableItem))
			{
				TempConsumableItemDataArray.Add(ItemData);
			}

			if (ItemData.ItemTag.MatchesTag(ItemTags::SkillItem))
			{
				TempSkillItemDataArray.Add(ItemData);
			}

			if (ItemData.ItemTag.MatchesTag(ItemTags::OtherItem))
			{
				TempOtherItemDataArray.Add(ItemData);
			}
		}
	}

	InventoryWeaponItemDataArray = TempWeaponItemDataArray;
	InventoryAccessoryItemDataArray = TempAccessoryItemDataArray;
	InventoryConsumableItemDataArray = TempConsumableItemDataArray;
	InventorySkillItemDataArray = TempSkillItemDataArray;
	InventoryOtherItemDataArray = TempOtherItemDataArray;
}

void UNewInventoryItemContainer::SetCurrentDataArray()
{
	switch (DisplayItemFilter)
	{
	case EDisplayItemFilter::AllItems :
		{
			CurrentItemDataArray = InventoryAllItemDataArray;
		}
	case EDisplayItemFilter::WeaponItems :
		{
			CurrentItemDataArray = InventoryWeaponItemDataArray;
		}
	case EDisplayItemFilter::AccessoryItems :
		{
			CurrentItemDataArray = InventoryAccessoryItemDataArray;
		}
	case EDisplayItemFilter::ConsumableItems :
		{
			CurrentItemDataArray = InventoryConsumableItemDataArray;
		}
	case EDisplayItemFilter::SkillItems :
		{
			CurrentItemDataArray =  InventorySkillItemDataArray;
		}
	case EDisplayItemFilter::OtherItems :
		{
			CurrentItemDataArray =  InventoryOtherItemDataArray;
		}
	}
}

void UNewInventoryItemContainer::SetFocusIndex(const int32 NewFocusIndex)
{
	switch (DisplayItemFilter)
	{
	case EDisplayItemFilter::AllItems :
		{
			ChangeFocusIndex(NewFocusIndex);
		}
	case EDisplayItemFilter::WeaponItems :
		{
			ChangeFocusIndex(NewFocusIndex);
		}
	case EDisplayItemFilter::AccessoryItems :
		{
			ChangeFocusIndex(NewFocusIndex);
		}
	case EDisplayItemFilter::ConsumableItems :
		{
			ChangeFocusIndex(NewFocusIndex);
		}
	case EDisplayItemFilter::OtherItems :
		{
			ChangeFocusIndex(NewFocusIndex);
		}
	case EDisplayItemFilter::SkillItems :
		{
			ChangeFocusIndex(NewFocusIndex);
		}
	}
}
