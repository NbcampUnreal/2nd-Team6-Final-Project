// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Util/GameTagList.h"
#include "EnumAndStruct/EDisplayItemFilter.h"
#include "UI/BaseContent.h"
#include "NewItemSlot.generated.h"

DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnItemSlotGetFocusEvent, FGameplayTag, int32, FName);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnItemSlotClickedEvent, EDisplayItemFilter);

class UBorder;
class USizeBox;
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

	void SetInfo(const FGameplayTag NewItemTag, UTexture2D* NewItemIcon, const int32 NewItemQuantity);

protected:
	virtual void SetInfo() override;

	UFUNCTION(BlueprintCallable)
	void BroadcastButtonClickEvent() const;

	virtual void NativePreConstruct() override;

protected:
	UPROPERTY(BlueprintReadOnly)
	FGameplayTag ItemTag;
	
	UPROPERTY(BlueprintReadWrite)
	int32 ItemQuantity = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SlotName;

	// Widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Size = {100.f,100.f};
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UBorder> ItemImage;
	
	UPROPERTY(BLueprintReadOnly, meta=(BindWidget))
	TObjectPtr<USizeBox> Sizer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDisplayItemFilter SlotItemFilter;
};
