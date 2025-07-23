// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Util/GameTagList.h"
#include "Blueprint/UserWidget.h"
#include "EnumAndStruct/EDisplayItemFilter.h"
#include "Interface/UIInterface.h"
#include "NewEquipmentSubUI.generated.h"

class UItemComponent;
class UStatusComponent;
class UNewItemSlotContainer;
class UNewInventoryItemContainer;
class UBorder;
class UNewItemInfoCard;
class UNewShotcutButton;

UCLASS()
class DOMINIONPROTOCOL_API UNewEquipmentSubUI : public UUserWidget, public IUIInterface
{
	GENERATED_BODY()

public:
	// Getter 
	UFUNCTION()
	virtual UInputMappingContext* GetInputMappingContext_Implementation() const override;

	// Setter
	void SetFocusSlotItemTag(const FGameplayTag NewItemTag) { FocusSlotItemTag = NewItemTag;}
	
	void SetFocusSlotItemQuantity(const int32 NewSlotItemQuantity) { FocusSlotItemQuantity = NewSlotItemQuantity; }

	void SetFocusSlotName(const FName NewSlotName) { FocusSlotName = NewSlotName; }
	
	void SetFocusInventoryItemTag(const FGameplayTag NewItemTag) { FocusInventoryItemTag = NewItemTag; }

	void SetFocusInventoryItemQuantity(const int32 NewInventoryItemQuantity) { FocusInventoryItemQuantity = NewInventoryItemQuantity;}

	void SetClickedSlotItemFilter(const EDisplayItemFilter NewSlotItemFilter) { ClickedSlotItemFilter = NewSlotItemFilter; }

protected:
	void IncreaseFocusIndex() const;

	void DecreaseFocusIndex() const;
	
	void SequenceChangeFocusSlotItemEvent(const FGameplayTag NewItemTag, const int32 NewItemQuantity, const FName NewItemSlotName);

	void SequenceChangeClickedSlotItemEvent (const EDisplayItemFilter NewItemFilter);

	void SequenceChangeFocusInventoryItemEvent(const FGameplayTag NewItemTag, const int32 NewItemQuantity);

	void SequenceChangeClickedInventoryItemEvent() const;
	
	void ShowInventoryItemContainer();

	void HideInventoryItemContainer();
	
	UFUNCTION()
	void EquipItemToSlot() const;

	UFUNCTION()
	void UnequipItemToSlot() const;

	// Refresh
	UFUNCTION()
	void RefreshWidget();
	
	UFUNCTION()
	void RequestRefreshWidget(const ESlateVisibility NewVisibility);
	
	UFUNCTION(BlueprintImplementableEvent)
	void RequestRefreshStatusPlate();

	// Bind Section
	void BindUpdateInventorySlotDataDelegates();

	void BindFocusItemChangedDelegates();

	void BindClickedItemChangedDelegates();

	void BindCloseInventoryButtonClickedDelegates();

	void BindInputActionDelegates();

	// Lift Cycle
	virtual void NativeConstruct() override;
	
protected:
	UPROPERTY()
	FGameplayTag FocusSlotItemTag;
	
	int32 FocusSlotItemQuantity = 0;
	
	FName FocusSlotName;
	
	UPROPERTY()
	FGameplayTag FocusInventoryItemTag;

	int32 FocusInventoryItemQuantity = 0;

	UPROPERTY()
	EDisplayItemFilter ClickedSlotItemFilter = EDisplayItemFilter::AllItems;

	bool bIsInventoryItemContainerVisible = false;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UItemComponent> ItemComponent;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UStatusComponent> StatusComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputMappingContext> EquipmentSubUIMappingContext;

	// Widget
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UNewItemSlotContainer> ItemSlotContainer;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UNewInventoryItemContainer> InventoryItemContainer;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UBorder> InventoryBorder;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UNewItemInfoCard> ItemInfo;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UNewShotcutButton> CloseInventoryButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UNewShotcutButton> EquipButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UNewShotcutButton> UnequipButton;
};
