// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnumAndStruct/EDisplayItemFilter.h"
#include "UI/BaseContentContainer.h"
#include "NewItemFilterContainer.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnCurrentItemFilterChangedEvent, EDisplayItemFilter)

UCLASS()
class DOMINIONPROTOCOL_API UNewItemFilterContainer : public UBaseContentContainer
{
	GENERATED_BODY()

public:
	FOnCurrentItemFilterChangedEvent OnCurrentItemFilterChangedEvent;
	
	UFUNCTION()
	void SetCurrentItemFilter(const EDisplayItemFilter NewItemFilter);

	UFUNCTION()
	EDisplayItemFilter GetCurrentItemFilter() const { return CurrentItemFilter; }

protected:
	virtual void NativeConstruct() override;

	void BindChangeItemFilterFocusDelegates();

protected:
	UPROPERTY(BlueprintReadWrite)
	EDisplayItemFilter CurrentItemFilter;
};
