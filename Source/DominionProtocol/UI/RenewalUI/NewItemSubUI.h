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

UCLASS()
class DOMINIONPROTOCOL_API UNewItemSubUI : public UUserWidget, public IUIInterface
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual UInputMappingContext* GetInputMappingContext_Implementation() const override;

	UFUNCTION()
	void RefreshWidget() const;

	// Setter
	void SetFocusItemInfo(const FGameplayTag NewItemTag, const int32 NewItemQuantity);

	void SetCurrentItemFilter(const EDisplayItemFilter NewItemFilter);

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void RequestRefreshWidget(const ESlateVisibility NewVisibility);

	void BindInputActionDelegates();

	void BindItemFilterChangedDelegates();

	void BindFocusItemChangedDelegates();

protected:
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

	UPROPERTY()
	FGameplayTag FocusItemTag;

	int32 FocusItemQuantity = 0;

	UPROPERTY()
	EDisplayItemFilter CurrentItemFilter = EDisplayItemFilter::AllItems;
};
