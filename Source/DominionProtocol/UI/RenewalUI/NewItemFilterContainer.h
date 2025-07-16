// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnumAndStruct/EDisplayItemFilter.h"
#include "UI/BaseContentContainer.h"
#include "NewItemFilterContainer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDisplayItemFilterChangedEvent, EDisplayItemFilter, CurrentItemFilter);

UCLASS()
class DOMINIONPROTOCOL_API UNewItemFilterContainer : public UBaseContentContainer
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnDisplayItemFilterChangedEvent OnDisplayItemFilterChangedEvent;

	UFUNCTION(BlueprintCallable)
	void SetCurrentItemFilter(const EDisplayItemFilter NewItemFilter);

protected:
	virtual void NativeConstruct() override;

	void BindInputActionDelegates();

protected:
	UPROPERTY(BlueprintReadWrite)
	EDisplayItemFilter CurrentItemFilter;
};
