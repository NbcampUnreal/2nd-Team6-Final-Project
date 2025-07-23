// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnumAndStruct/EDisplayItemFilter.h"
#include "UI/BaseContentContainer.h"
#include "NewInventoryItemContainer.generated.h"

struct FItemUISlotData;
class UItemComponent;

UCLASS()
class DOMINIONPROTOCOL_API UNewInventoryItemContainer : public UBaseContentContainer
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void SetContentInfo();

	UFUNCTION()
	void RefreshWidget(const EDisplayItemFilter NewDisplayItemFilter);
	
	void SaveFocusIndex(const EDisplayItemFilter NewDisplayItemFilter);

	// Getter
	int32 GetDisplayFocusIndex(const EDisplayItemFilter NewDisplayItemFilter) const;
	
	virtual void ChangeFocusIndex(const int32 NewFocusIndex) override;
	
protected:
	UFUNCTION()
	void SetItemDataArrays();

	UFUNCTION()
	void SetCurrentDataArray(const EDisplayItemFilter NewDisplayItemFilter);

	UFUNCTION()
	void SetFocusIndex(const EDisplayItemFilter NewDisplayItemFilter, const int32 NewFocusIndex);

	virtual void NativeConstruct() override;

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UItemComponent> ItemComponent;

	UPROPERTY(BlueprintReadOnly)
	TArray<FItemUISlotData> InventoryAllItemDataArray;
	
	UPROPERTY(BlueprintReadOnly)
	TArray<FItemUISlotData> InventoryWeaponItemDataArray;
	
	UPROPERTY(BlueprintReadOnly)
	TArray<FItemUISlotData> InventoryAccessoryItemDataArray;
	
	UPROPERTY(BlueprintReadOnly)
	TArray<FItemUISlotData> InventoryConsumableItemDataArray;
	
	UPROPERTY(BlueprintReadOnly)
	TArray<FItemUISlotData> InventorySkillItemDataArray;
	
	UPROPERTY(BlueprintReadOnly)
	TArray<FItemUISlotData> InventoryOtherItemDataArray;
	
	UPROPERTY(BlueprintReadOnly)
	TArray<FItemUISlotData> CurrentItemDataArray;
	
	int32 AllItemsFocusIndex = 0;		
	
	int32 WeaponItemsFocusIndex = 0;		
	
	int32 AccessoryItemsFocusIndex = 0;	
	
	int32 ConsumableItemsFocusIndex = 0;	
	
	int32 SkillItemsFocusIndex = 0;		
	
	int32 OtherItemsFocusIndex = 0;		
};
