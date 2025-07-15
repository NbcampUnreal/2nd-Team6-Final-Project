// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NewEquipmentSubUI.generated.h"

class UItemComponent;
class UStatusComponent;

UCLASS()
class DOMINIONPROTOCOL_API UNewEquipmentSubUI : public UUserWidget
{
	GENERATED_BODY()


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
};
