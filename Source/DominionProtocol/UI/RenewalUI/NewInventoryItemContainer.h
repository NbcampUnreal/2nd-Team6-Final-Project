// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnumAndStruct/EDisplayItemFilter.h"
#include "UI/BaseContentContainer.h"
#include "NewInventoryItemContainer.generated.h"

struct FItemUISlotData;

UCLASS()
class DOMINIONPROTOCOL_API UNewInventoryItemContainer : public UBaseContentContainer
{
	GENERATED_BODY()


public:
	UFUNCTION()
	void OnUpdateInventoryItemList();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateInventoryItemList();
	
protected:
	virtual void NativeConstruct() override;
	
	void BindInventoryDelegates();
	

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class UItemComponent> ItemComponent;

	UPROPERTY(BlueprintReadOnly)
	TArray<FItemUISlotData> InventoryAllItems;
	UPROPERTY(BlueprintReadOnly)
	TArray<FItemUISlotData> WeaponItemsItems;
	UPROPERTY(BlueprintReadOnly)
	TArray<FItemUISlotData> AccessoryItemsItems;
	UPROPERTY(BlueprintReadOnly)
	TArray<FItemUISlotData> SkillItemsItems;
	UPROPERTY(BlueprintReadOnly)
	TArray<FItemUISlotData> ConsumableItemsArray;
	UPROPERTY(BlueprintReadOnly)
	TArray<FItemUISlotData> OtherItemsArray;
	
	UPROPERTY(BlueprintReadWrite)
	EDisplayItemFilter LastDisplayArray = EDisplayItemFilter::AllItems;
	
};
