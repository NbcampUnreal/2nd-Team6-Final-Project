// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseContentContainer.generated.h"

class UBaseContent;

UCLASS()
class DOMINIONPROTOCOL_API UBaseContentContainer : public UUserWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION()
	void ChangeFocusIndex(const int32 NewFocusIndex);

	UFUNCTION()
	void IncreaseFocusIndex();

	UFUNCTION()
	void DecreaseFocusIndex();

	virtual void NativeConstruct() override;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UPanelWidget> ContentContainer;

	UPROPERTY()
	TArray<TObjectPtr<UBaseContent>> ContentArray;
	
	int32 CurrentFocusIndex = -1;

	int32 MaxFocusIndex = 0;
};
