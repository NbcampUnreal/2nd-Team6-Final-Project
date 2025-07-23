// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Util/GameTagList.h"
#include "EnumAndStruct/EDisplayItemFilter.h"
#include "UI/BaseContent.h"
#include "NewItemSlot.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemSlotClickedEvent, FName, EDisplayItemFilter);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemSlotGetFocusEvent, FGameplayTag, int32);

class UBorder;
class USizeBox;
class UItemComponent;
class UNewItemSlotContainer;

UCLASS()
class DOMINIONPROTOCOL_API UNewItemSlot : public UBaseContent
{
	GENERATED_BODY()

public:
	FOnItemSlotClickedEvent OnItemSlotClickedEvent;
	FOnItemSlotGetFocusEvent OnItemSlotGetFocusEvent;

	virtual void GetFocus() override;

	FName GetSlotName() const { return SlotName; }
	
	int32 GetItemQuantity() const { return ItemQuantity; }

	void SetInfo(const FGameplayTag NewItemTag, const int32 NewItemQuantity);

	void SetOwingWidget(UNewItemSlotContainer* NewEquippedSlotsContainer) { OwningWidget = NewEquippedSlotsContainer; }

protected:
	virtual void SetInfo() override;

	UFUNCTION(BlueprintCallable)
	void ItemSlotClickedEvent() const;
	
	bool SearchingSlotItem();
	
	virtual void NativeConstruct() override;

	virtual void NativePreConstruct() override;

protected:
	UPROPERTY(BlueprintReadWrite)
	int32 ItemQuantity = 0;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UBorder> ItemImage;
	
	UPROPERTY(BLueprintReadOnly, meta=(BindWidget))
	TObjectPtr<USizeBox> Sizer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDisplayItemFilter SlotItemFilter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Size = {100.f,100.f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SlotName;

	UPROPERTY(BlueprintReadOnly)
	FGameplayTag ItemTag;

	UPROPERTY()
	TObjectPtr<UItemComponent> ItemComponent;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UNewItemSlotContainer> OwningWidget;
};
