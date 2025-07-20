// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemInventory/ItemUISlotData.h"
#include "Blueprint/UserWidget.h"
#include "NewItemSlotContainer.generated.h"

class UTextBlock;
class UNewItemSlot;

UCLASS()
class DOMINIONPROTOCOL_API UNewItemSlotContainer : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetItemSlotInfo(TMap<FName, FItemUISlotData> UpdatedSlotMap);

	UFUNCTION(BlueprintCallable)
	void ChangeFocusIndex(const int32 NewFocusIndex);

	UFUNCTION(BlueprintCallable)
	void IncreaseFocusIndex();

	UFUNCTION(BlueprintCallable)
	void DecreaseFocusIndex();

	void RefreshWidget();

	TArray<TObjectPtr<UNewItemSlot>> GetSlotWidgetArray() const { return SlotWidgetArray; }

protected:
	UFUNCTION()
	void UpdateConsumableSlotsCount() const;
	
	void OnUpdateEquippableSlotItemMap();
	
	void OnUpdateConsumableSlotItemMap();
	
	virtual void NativeConstruct() override;
	
	void BindItemSlotsDelegate();
	
	void BindInputActionsDelegate();

protected:
	UPROPERTY()
	TObjectPtr<class UItemComponent> ItemComponent;

	UPROPERTY(BlueprintReadOnly)
	TMap<FName, FItemUISlotData> EquippableSlotMap;

	UPROPERTY(BlueprintReadOnly)
	TMap<FName, FItemUISlotData> ConsumableSlotMap;

	UPROPERTY(BlueprintReadWrite)
	int32 CurrentFocusIndex = -1;

	int32 MaxFocusIndex = -1;

	TArray<TObjectPtr<UNewItemSlot>> SlotWidgetArray;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UNewItemSlot> AccessorySlot_Primary;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UNewItemSlot> AccessorySlot_Secondary;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UNewItemSlot> WeaponSlot_Primary;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UNewItemSlot> WeaponSlot_Secondary;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UNewItemSlot> SkillSlot;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UNewItemSlot> ConsumableSlot_Primary;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UNewItemSlot> ConsumableSlot_Secondary;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UNewItemSlot> ConsumableSlot_Tertiary;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> ConsumableItemCount1;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> ConsumableItemCount2;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> ConsumableItemCount3;
};
