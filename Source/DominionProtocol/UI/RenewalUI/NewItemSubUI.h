// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interface/UIInterface.h"
#include "NewItemSubUI.generated.h"

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
	void RefreshWidget();

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void RequestRefreshWidget(const ESlateVisibility NewVisibility);

	void BindInputActionDelegates();

	void BindItemFilterChangedDelegates();

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
};
