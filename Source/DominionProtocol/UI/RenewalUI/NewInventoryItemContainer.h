// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "EnumAndStruct/EDisplayItemFilter.h"
#include "UI/BaseContentContainer.h"
#include "NewInventoryItemContainer.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnLastDisplayArrayChangedEvent);

struct FItemUISlotData;

UCLASS()
class DOMINIONPROTOCOL_API UNewInventoryItemContainer : public UBaseContentContainer
{
	GENERATED_BODY()

public:
	FOnLastDisplayArrayChangedEvent OnLastDisplayArrayChangedEvent;
	
	UFUNCTION(BlueprintCallable)
	void SetLastDisplayArray(const EDisplayItemFilter& NewItemDisplay);

	UFUNCTION(BlueprintCallable)
	void SetClickedSlotName(const FName& NewClickedSlotName) { ClickedSlotName = NewClickedSlotName; }

	UFUNCTION(BlueprintCallable)
	void SetClickedInventoryItemTag(const FGameplayTag& NewClickedInventoryItemTag) { ClickedInventoryItemTag = NewClickedInventoryItemTag; }
	
protected:
	virtual void ChangeFocusIndex(const int32 NewFocusIndex) override;
	
	void RefreshInventoryItemInfo();

	void SetDisplayFocusIndex(const int32 NewFocusIndex);

	UFUNCTION()
	void SetInventoryItemInfo();

	UFUNCTION()
	void SetCurrentItemDataArray();

	UFUNCTION()
	void SetFocusIndex();
	
	void EquipItemToClick();
	
	void UnEquipItemToClick();

	UFUNCTION()
	void SetInventoryItemOwningWidget();

	UFUNCTION()
	void BindInventoryRefreshDelegates();

	void BindInputActionsDelegates();

	virtual void NativeConstruct() override;

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class UItemComponent> ItemComponent;

	UPROPERTY(BlueprintReadOnly)
	TArray<FItemUISlotData> InventoryAllItemDataArray;
	
	UPROPERTY(BlueprintReadOnly)
	TArray<FItemUISlotData> CurrentItemDataArray;
	
	UPROPERTY(BlueprintReadWrite)
	EDisplayItemFilter LastDisplayArray = EDisplayItemFilter::AllItems;

	FName ClickedSlotName;

	FGameplayTag ClickedInventoryItemTag; 
	
	int32 AllItemsIndex = 0;		
	
	int32 WeaponItemsIndex = 0;		
	
	int32 AccessoryItemsIndex = 0;	
	
	int32 ConsumableItemsIndex = 0;	
	
	int32 SkillItemsIndex = 0;		
	
	int32 OtherItemsIndex = 0;		
};
