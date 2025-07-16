// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseContentContainer.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnFocusIndexChangedEvent, int32);

class UBaseContent;

UCLASS(Abstract)
class DOMINIONPROTOCOL_API UBaseContentContainer : public UUserWidget
{
	GENERATED_BODY()

public:
	FOnFocusIndexChangedEvent OnFocusIndexChanged;

protected:
	UFUNCTION(BlueprintCallable)
    virtual void ChangeFocusIndex(const int32 NewFocusIndex);
    
    UFUNCTION(BlueprintCallable)
    void IncreaseFocusIndex();
    
    UFUNCTION(BlueprintCallable)
    void DecreaseFocusIndex();
          	
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UPanelWidget> ContentContainer;

	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<UBaseContent>> ContentArray;
	
	UPROPERTY(BlueprintReadOnly)
	int32 CurrentFocusIndex = -1;

	int32 MaxFocusIndex = 0;
};
