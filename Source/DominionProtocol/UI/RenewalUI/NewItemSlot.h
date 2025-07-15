// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "EnumAndStruct/EDisplayItemFilter.h"
#include "UI/BaseContent.h"
#include "NewItemSlot.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemSlotClickedEvent, FName, SlotName, EDisplayItemFilter, SlotItemFilter);

class UBorder;
class USizeBox;
class UItemComponent;

UCLASS()
class DOMINIONPROTOCOL_API UNewItemSlot : public UBaseContent
{
	GENERATED_BODY()

public:
	FOnItemSlotClickedEvent OnItemSlotClickedEvent;

protected:
	bool SearchingSlotItem();
	
	virtual void NativeConstruct() override;

	virtual void NativePreConstruct() override;


protected:
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
	FGameplayTag ItemTag = FGameplayTag::RequestGameplayTag(FName("None"));

	UPROPERTY()
	TObjectPtr<UItemComponent> ItemComponent;
};
