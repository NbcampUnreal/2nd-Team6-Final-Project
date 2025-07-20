// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RenewalUI/NewItemInfoCard.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ItemInventory/ItemData.h"

void UNewItemInfoCard::SetInfo(const FGameplayTag ItemTag, const int32 ItemQuantity)
{
	// 1. Display 설정
	if (!ItemTag.IsValid())
	{
		SetVisibility(ESlateVisibility::Hidden);
		return;
	}
	SetVisibility(ESlateVisibility::Visible);

	// 2. 데이터 조회 
	const FName ItemTagName = ItemTag.GetTagName();
	const FItemData* ItemData = ItemDataTable->FindRow<FItemData>(ItemTagName, TEXT(""));

	const FString ItemNameString = ItemData->ItemName;
	const FText ItemNameText = FText::FromString(ItemNameString);
	ItemName->SetText(ItemNameText);

	ItemImage->SetBrushFromTexture(ItemData->ItemIcon);

	const FText ItemAmountText = FText::FromString(FString::Printf(TEXT("%d / %d"), ItemQuantity, ItemData->MaxItemQuantity));
	ItemAmount->SetText(ItemAmountText);

	const FString ResultString = ItemData->ItemDescription.ToString().Replace(TEXT("<br>"), TEXT("\n"));
	const FText ItemDescriptionText = FText::FromString(ResultString);
	ItemExplain->SetText(ItemDescriptionText);

	// 3. Item Effects Setting
	const EItemType ItemType = ItemData->ItemType;
	SetItemEffectsInfo(ItemTag, ItemType);
}

void UNewItemInfoCard::NativeConstruct()
{
	Super::NativeConstruct();

	ensureMsgf(ItemDataTable, TEXT("UNewItemInfoCard : ItemDataTable is not set."));
}
