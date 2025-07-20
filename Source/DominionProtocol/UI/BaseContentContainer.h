// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseContentContainer.generated.h"

class UBaseContent;

UCLASS(Abstract)
class DOMINIONPROTOCOL_API UBaseContentContainer : public UUserWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION()
    virtual void ChangeFocusIndex(const int32 NewFocusIndex);
    
    UFUNCTION()
    virtual void IncreaseFocusIndex();
    
    UFUNCTION()
    virtual void DecreaseFocusIndex();
          	
	virtual void NativeConstruct() override;

	void BindFocusIndexChangedEventDelegates();

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UPanelWidget> ContentContainer;

	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<UBaseContent>> ContentArray;
	
	UPROPERTY(BlueprintReadOnly)
	int32 CurrentFocusIndex = -1;

	int32 MaxFocusIndex = 0;
};
