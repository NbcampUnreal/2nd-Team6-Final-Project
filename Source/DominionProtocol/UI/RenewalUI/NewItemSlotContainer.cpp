// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RenewalUI/NewItemSlotContainer.h"

#include "NewItemSlot.h"
#include "Components/TextBlock.h"
#include "Components/ItemComponent/ItemComponent.h"
#include "Player/InGameController.h"


void UNewItemSlotContainer::SetItemSlotInfo(TMap<FName, FItemUISlotData> UpdatedSlotMap)
{
	for (UNewItemSlot* SlotWidget : SlotWidgetArray)
	{
		if (SlotWidget)
		{
			const FName SlotName = SlotWidget->GetSlotName();
			const FItemUISlotData* SlotData = UpdatedSlotMap.Find(SlotName);
			if (SlotData && SlotData->ItemTag.IsValid())
			{
				const FGameplayTag SlotItemTag = SlotData->ItemTag;
				UTexture2D* SlotItemIcon = SlotData->ItemIcon;
				const int32 SlotItemQuantity = SlotData->CurrentQuantity;
				SlotWidget->SetInfo(SlotItemTag, SlotItemIcon, SlotItemQuantity);
			}
		}
	}
}

void UNewItemSlotContainer::ChangeFocusIndex(const int32 NewFocusIndex)
{
	for (int32 i = 0; i < SlotWidgetArray.Num(); i++)
	{
		if (SlotWidgetArray.IsValidIndex(i))
		{
			if (i == NewFocusIndex)
			{
				SlotWidgetArray[i]->GetFocus();
				CurrentFocusIndex = NewFocusIndex;	
			}
			else
			{
				SlotWidgetArray[i]->LoseFocus();
			}	
		}
	}
}

void UNewItemSlotContainer::IncreaseFocusIndex()
{
	if (CurrentFocusIndex >= MaxFocusIndex)
	{
		return;
	}

	ChangeFocusIndex(CurrentFocusIndex + 1);
}

void UNewItemSlotContainer::DecreaseFocusIndex()
{
	if (CurrentFocusIndex <= 0)
	{
		return;
	}

	ChangeFocusIndex(CurrentFocusIndex - 1);
}

void UNewItemSlotContainer::RefreshWidget()
{
	OnUpdateConsumableSlotItemMap();
	OnUpdateEquippableSlotItemMap();
}

void UNewItemSlotContainer::NativeConstruct()
{
	Super::NativeConstruct();

	BindItemSlotsDelegate();
	BindInputActionsDelegate();

	SlotWidgetArray.AddUnique(AccessorySlot_Primary);
	SlotWidgetArray.AddUnique(AccessorySlot_Secondary);
	SlotWidgetArray.AddUnique(SkillSlot);
	SlotWidgetArray.AddUnique(WeaponSlot_Primary);
	SlotWidgetArray.AddUnique(WeaponSlot_Secondary);
	SlotWidgetArray.AddUnique(ConsumableSlot_Primary);
	SlotWidgetArray.AddUnique(ConsumableSlot_Secondary);
	SlotWidgetArray.AddUnique(ConsumableSlot_Tertiary);

	for (int32 i = 0; i < SlotWidgetArray.Num(); i++)
	{
		SlotWidgetArray[i]->SetContentIndex(i);
		SlotWidgetArray[i]->RequestChangingFocusIndexEvent.AddUObject(this, &UNewItemSlotContainer::ChangeFocusIndex);
	}

	MaxFocusIndex = SlotWidgetArray.Num() - 1;
}

void UNewItemSlotContainer::BindItemSlotsDelegate()
{
	const APawn* PlayerCharacter = GetOwningPlayerPawn();
	if (PlayerCharacter)
	{
		ItemComponent = PlayerCharacter->GetComponentByClass<UItemComponent>();
		if (ItemComponent)
		{
			ItemComponent->OnInventoryEquippedSlotItemsChanged.AddUObject(this, &UNewItemSlotContainer::OnUpdateEquippableSlotItemMap);
			ItemComponent->OnInventoryConsumableSlotItemsChanged.AddUObject(this, &UNewItemSlotContainer::OnUpdateConsumableSlotItemMap);
		}
	}
}

void UNewItemSlotContainer::BindInputActionsDelegate()
{
	auto* InGameController = Cast<AInGameController>(GetOwningPlayer());
	if (InGameController)
	{
		InGameController->OnEquipmentUIMoveSelectionUpEvent.AddUObject(this, &UNewItemSlotContainer::DecreaseFocusIndex);
		InGameController->OnEquipmentUIMoveSelectionDownEvent.AddUObject(this, &UNewItemSlotContainer::IncreaseFocusIndex);
	}
}

void UNewItemSlotContainer::OnUpdateEquippableSlotItemMap()
{
	if (ItemComponent)
	{
		EquippableSlotMap = ItemComponent->GetEquippedDisplayItems();
		SetItemSlotInfo(EquippableSlotMap);
	}
}

void UNewItemSlotContainer::OnUpdateConsumableSlotItemMap()
{
	if (ItemComponent)
	{
		ConsumableSlotMap = ItemComponent->GetConsumableDisplayItems();
		SetItemSlotInfo(ConsumableSlotMap);
		UpdateConsumableSlotsCount();
	}
}

void UNewItemSlotContainer::UpdateConsumableSlotsCount() const 
{
	const int32 PrimaryItemQuantity = ConsumableSlot_Primary->GetItemQuantity();
	const int32 SecondaryItemQuantity = ConsumableSlot_Secondary->GetItemQuantity();
	const int32 TertiaryItemQuantity = ConsumableSlot_Tertiary->GetItemQuantity();
	
	ConsumableItemCount1->SetText(FText::AsNumber(PrimaryItemQuantity));
	ConsumableItemCount2->SetText(FText::AsNumber(SecondaryItemQuantity));
	ConsumableItemCount3->SetText(FText::AsNumber(TertiaryItemQuantity));
}
