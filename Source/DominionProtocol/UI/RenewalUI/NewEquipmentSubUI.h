// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Blueprint/UserWidget.h"
#include "EnumAndStruct/EDisplayItemFilter.h"
#include "Interface/UIInterface.h"
#include "NewEquipmentSubUI.generated.h"

class UItemComponent;
class UStatusComponent;
class UNewItemSlotContainer;
class UNewInventoryItemContainer;
class UBorder;

UCLASS()
class DOMINIONPROTOCOL_API UNewEquipmentSubUI : public UUserWidget, public IUIInterface
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual UInputMappingContext* GetInputMappingContext_Implementation() const override;

	UFUNCTION()
	void RefreshEquipmentSubUI();

protected:
	void ShowInventoryItemContainer(const FName SlotName, const EDisplayItemFilter DisplayFilter) const;
	
	virtual void NativeConstruct() override;
	
	void BindEquippedSlotsDelegates();

	UFUNCTION()
	void OnUpdateEquippedSlots();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateEquippedSlots();

	void BindSlotClickedDelegates();
	
protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UItemComponent> ItemComponent;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UStatusComponent> StatusComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputMappingContext> EquipmentSubUIMappingContext;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UNewItemSlotContainer> EquippedSlotContainer;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UNewInventoryItemContainer> InventoryItemContainer;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UBorder> InventoryBorder;
};
