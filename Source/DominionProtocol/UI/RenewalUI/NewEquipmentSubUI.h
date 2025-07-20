// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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
	void RequestRefreshWidget(const ESlateVisibility NewVisibility);
	
	UFUNCTION()
	void RefreshWidget();

protected:
	void ShowInventoryItemContainer() const;

	UFUNCTION(BlueprintImplementableEvent)
	void RequestRefreshStatusPlate();

	void BindRefreshWidgetDelegates();
	
	virtual void NativeConstruct() override;
	
protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UItemComponent> ItemComponent;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UStatusComponent> StatusComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputMappingContext> EquipmentSubUIMappingContext;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UNewItemSlotContainer> ItemSlotContainer;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UNewInventoryItemContainer> InventoryItemContainer;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UBorder> InventoryBorder;
};
