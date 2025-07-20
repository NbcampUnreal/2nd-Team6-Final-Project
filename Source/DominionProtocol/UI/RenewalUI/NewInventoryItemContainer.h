// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "EnumAndStruct/EDisplayItemFilter.h"
#include "UI/BaseContentContainer.h"
#include "NewInventoryItemContainer.generated.h"

struct FItemUISlotData;
class UNewEquipmentSubUI;
class UNewItemSubUI;

UCLASS()
class DOMINIONPROTOCOL_API UNewInventoryItemContainer : public UBaseContentContainer
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void SetContentInfo();

	void RefreshWidget();

	// Setter
	void SetDisplayItemFilter(const EDisplayItemFilter NewDisplayItemFilter);
	void SetClickedItemTag(const FGameplayTag NewClickedItemTag);
	void SetClickedItemQuantity(const int32 NewClickedItemQuantity);

	// Getter
	EDisplayItemFilter GetDisplayItemFilter() const { return DisplayItemFilter; }
	FGameplayTag GetClickedItemTag() const { return ClickedItemTag; }
	int32 GetClickedItemQuantity() const { return ClickedItemQuantity; }
	
	virtual void ChangeFocusIndex(const int32 NewFocusIndex) override;
	
protected:
	void SetDisplayFocusIndex(const int32 NewFocusIndex);

	UFUNCTION()
	void SetCurrentItemDataArray();

	UFUNCTION()
	void SetFocusIndex();

	void BindInputActionsDelegates();

	void BindChangeItemFilterFocusDelegates();

	virtual void NativeConstruct() override;

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class UItemComponent> ItemComponent;

	UPROPERTY(BlueprintReadOnly)
	TArray<FItemUISlotData> InventoryAllItemDataArray;
	
	UPROPERTY(BlueprintReadOnly)
	TArray<FItemUISlotData> CurrentItemDataArray;
	
	UPROPERTY(BlueprintReadWrite)
	EDisplayItemFilter DisplayItemFilter = EDisplayItemFilter::AllItems;

	FGameplayTag ClickedItemTag;

	int32 ClickedItemQuantity;
	
	int32 AllItemsFocusIndex = 0;		
	
	int32 WeaponItemsFocusIndex = 0;		
	
	int32 AccessoryItemsFocusIndex = 0;	
	
	int32 ConsumableItemsFocusIndex = 0;	
	
	int32 SkillItemsFocusIndex = 0;		
	
	int32 OtherItemsFocusIndex = 0;		
};
