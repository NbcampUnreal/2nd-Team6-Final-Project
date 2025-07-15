// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interface/UIInterface.h"
#include "NewEquipmentSubUI.generated.h"

class UItemComponent;
class UStatusComponent;
class UNewEquippedSlotsContainer;
class UNewInventoryItemContainer;

UCLASS()
class DOMINIONPROTOCOL_API UNewEquipmentSubUI : public UUserWidget, public IUIInterface
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual UInputMappingContext* GetInputMappingContext_Implementation() const override;

	UFUNCTION()
	void RefreshEquipmentSubUI();

	UFUNCTION(BlueprintCallable)
	void UpdateStatusPlateInfo();

protected:
	virtual void NativeConstruct() override;
	
	void BindEquippedSlotsDelegates();

	UFUNCTION()
	void OnUpdateEquippedSlots();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateEquippedSlots();
	
protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UItemComponent> ItemComponent;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UStatusComponent> StatusComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputMappingContext> EquipmentSubUIMappingContext;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UNewEquippedSlotsContainer> EquippedSlotContainer;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UNewInventoryItemContainer> InventoryItemContainer;
	
};
