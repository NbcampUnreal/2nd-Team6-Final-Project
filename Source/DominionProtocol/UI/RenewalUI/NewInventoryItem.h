// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemInventory/ItemUISlotData.h"
#include "UI/BaseContent.h"
#include "NewInventoryItem.generated.h"

class UNewInventoryItemContainer;
class UImage;
class UTextBlock;
class UBorder;
class UItemComponent;

UCLASS()
class DOMINIONPROTOCOL_API UNewInventoryItem : public UBaseContent
{
	GENERATED_BODY()

public:
	virtual void SetInfo() override;
	
	void SetInfo(const FGameplayTag& ItemTag, UTexture2D* ItemTexture, const FString& ItemNameString, const FText& ItemDescription, int32
	                     CurrentItemQuantity, int32 MaxItemQuantity, EItemType ItemType);
	
	virtual void GetFocus() override;

	virtual void LoseFocus() override;

	void SetOwningWidget(UNewInventoryItemContainer* NewOwningWidget) { OwningWidget = NewOwningWidget;}

protected:
	UFUNCTION()
	void DisplayInfo();
	
	UFUNCTION(BlueprintImplementableEvent)
	void GetFocusEffects();

	UFUNCTION(BlueprintImplementableEvent)
	void LoseFocusEffects();

	virtual void NativeConstruct() override;

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UNewInventoryItemContainer> OwningWidget;
	
	UPROPERTY()
	TMap<FName, FGameplayTag> TotalItemSlotMap;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UImage> ItemIcon;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> ItemName;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> ItemAmount;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UBorder> EquipItemEffect;
	
	UPROPERTY()
	FItemUISlotData ItemData;

	bool bIsEquippedItem = false;
	
};
