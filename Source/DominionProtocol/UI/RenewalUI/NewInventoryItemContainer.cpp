// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RenewalUI/NewInventoryItemContainer.h"

#include "NewInventoryItem.h"
#include "Components/ItemComponent/ItemComponent.h"
#include "EnumAndStruct/EDisplayItemFilter.h"

void UNewInventoryItemContainer::NativeConstruct()
{
	Super::NativeConstruct();

	APawn* PlayerPawn = GetOwningPlayerPawn();
	if (PlayerPawn)
	{
		ItemComponent = PlayerPawn->GetComponentByClass<UItemComponent>();
	}
}

int32 UNewInventoryItemContainer::GetDisplayFocusIndex(const EDisplayItemFilter NewDisplayItemFilter) const
{
	switch (NewDisplayItemFilter)
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
}

void UNewInventoryItemContainer::RefreshWidget(const EDisplayItemFilter NewDisplayItemFilter)
{
	SetItemDataArrays();
	SetCurrentDataArray(NewDisplayItemFilter);
	SetContentInfo();

	const int32 NewFocusIndex = GetDisplayFocusIndex(NewDisplayItemFilter);
	SetFocusIndex(NewDisplayItemFilter, NewFocusIndex);
}

void UNewInventoryItemContainer::SaveFocusIndex(const EDisplayItemFilter NewDisplayItemFilter)
{
	switch (NewDisplayItemFilter)
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
	check(ItemComponent);

	const TArray<FItemUISlotData> InventoryArray = ItemComponent->GetInventoryDisplayItems();
	InventoryAllItemDataArray.Empty();
	InventoryAllItemDataArray.Append(InventoryArray);

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

	InventoryWeaponItemDataArray.Empty();
	InventoryWeaponItemDataArray.Append(TempWeaponItemDataArray);
	InventoryAccessoryItemDataArray.Empty();
	InventoryAccessoryItemDataArray.Append(TempAccessoryItemDataArray);
	InventoryConsumableItemDataArray.Empty();
	InventoryConsumableItemDataArray.Append(TempConsumableItemDataArray);
	InventorySkillItemDataArray.Empty();
	InventorySkillItemDataArray.Append(TempSkillItemDataArray);
	InventoryOtherItemDataArray.Empty();
	InventoryOtherItemDataArray.Append(TempOtherItemDataArray);
}

void UNewInventoryItemContainer::SetCurrentDataArray(const EDisplayItemFilter NewDisplayItemFilter)
{
	CurrentItemDataArray.Empty();
	
	switch (NewDisplayItemFilter)
	{
	case EDisplayItemFilter::AllItems :
		{
			CurrentItemDataArray.Append(InventoryAllItemDataArray);
		}
	case EDisplayItemFilter::WeaponItems :
		{
			CurrentItemDataArray.Append(InventoryWeaponItemDataArray);
		}
	case EDisplayItemFilter::AccessoryItems :
		{
			CurrentItemDataArray.Append(InventoryAccessoryItemDataArray);
		}
	case EDisplayItemFilter::ConsumableItems :
		{
			CurrentItemDataArray.Append(InventoryConsumableItemDataArray);
		}
	case EDisplayItemFilter::SkillItems :
		{
			CurrentItemDataArray.Append(InventorySkillItemDataArray);
		}
	case EDisplayItemFilter::OtherItems :
		{
			CurrentItemDataArray.Append(InventoryOtherItemDataArray);
		}
	}
}

void UNewInventoryItemContainer::SetFocusIndex(const EDisplayItemFilter NewDisplayItemFilter, const int32 NewFocusIndex)
{
	switch (NewDisplayItemFilter)
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
