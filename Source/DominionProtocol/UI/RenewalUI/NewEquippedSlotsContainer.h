// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemInventory/ItemUISlotData.h"
#include "Blueprint/UserWidget.h"
#include "NewEquippedSlotsContainer.generated.h"


UCLASS()
class DOMINIONPROTOCOL_API UNewEquippedSlotsContainer : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void OnUpdateEquippableSlotItems();
	UFUNCTION()
	void OnUpdateConsumableSlotItems();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateEquippableSlotItems();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateConsumableSlotItems();
	
protected:
	virtual void NativeConstruct() override;
	
	void BindItemSlotsDelegate();


protected:
	UPROPERTY()
	TObjectPtr<class UItemComponent> ItemComponent;

	UPROPERTY(BlueprintReadOnly)
	TMap<FName, FItemUISlotData> EquippableSlotMap;

	UPROPERTY(BlueprintReadOnly)
	TMap<FName, FItemUISlotData> ConsumableSlotMap;

	UPROPERTY(BlueprintReadWrite)
	int32 CurrentFocusIndex = -1;

	TArray<TObjectPtr<UUserWidget>> SlotWidgetArray;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UUserWidget> AccessorySlot_Primary;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UUserWidget> AccessorySlot_Secondary;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UUserWidget> WeaponSlot_Primary;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UUserWidget> WeaponSlot_Secondary;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UUserWidget> SkillSlot;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UUserWidget> ConsumableSlot_Primary;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UUserWidget> ConsumableSlot_Secondary;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UUserWidget> ConsumableSlot_Tertiary;
};
