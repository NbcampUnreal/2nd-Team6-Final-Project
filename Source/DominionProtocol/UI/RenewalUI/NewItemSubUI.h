// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Util/GameTagList.h"
#include "Blueprint/UserWidget.h"
#include "EnumAndStruct/EDisplayItemFilter.h"
#include "Interface/UIInterface.h"
#include "NewItemSubUI.generated.h"

enum class EDisplayItemFilter : uint8;
class UNewItemFilterContainer;
class UNewItemSlotContainer;
class UNewInventoryItemContainer;
class UNewItemInfoCard;
class UTextBlock;
class UItemComponent;

UCLASS()
class DOMINIONPROTOCOL_API UNewItemSubUI : public UUserWidget, public IUIInterface
{
	GENERATED_BODY()

public:
	// Getter
	UFUNCTION()
	virtual UInputMappingContext* GetInputMappingContext_Implementation() const override;

	// Setter
	void SetFocusItemTag(const FGameplayTag NewItemTag) { FocusItemTag = NewItemTag;}
	
	void SetFocusItemQuantity(const int32 NewItemQuantity) { FocusItemQuantity = NewItemQuantity;}

	void SetCurrentItemFilter(const EDisplayItemFilter NewItemFilter) { CurrentItemFilter = NewItemFilter; }

	void SetupItemTypeName();

protected:
	void SequenceChangeItemFilterEvent(const EDisplayItemFilter NewItemFilter);

	void SequenceChangeFocusItemEvent(const FGameplayTag NewItemTag, const int32 NewItemQuantity);

	// Refresh
	UFUNCTION()
	void RefreshWidget();
	
	UFUNCTION()
	void RequestRefreshWidget(const ESlateVisibility NewVisibility);
	
	// Bind Section
	void BindInputActionDelegates();

	void BindItemFilterChangedDelegates();

	void BindFocusItemChangedDelegates();

	void BindUpdateInventoryDataDelegates();

	// Lift Cycle
	virtual void NativeConstruct() override;

protected:
	UPROPERTY()
	FGameplayTag FocusItemTag;

	int32 FocusItemQuantity = 0;

	UPROPERTY()
	EDisplayItemFilter CurrentItemFilter = EDisplayItemFilter::AllItems;
	
	UPROPERTY()
	TObjectPtr<UItemComponent> ItemComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputMappingContext> ItemSubUIMappingContext;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UNewItemFilterContainer> ItemFilterContainer;
	
	// UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	// TObjectPtr<UNewItemSlotContainer> ItemSlotContainer;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UNewInventoryItemContainer> InventoryItemContainer;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UNewItemInfoCard> ItemInfoCard;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemTypeName;
};
