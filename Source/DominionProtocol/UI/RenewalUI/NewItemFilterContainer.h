// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnumAndStruct/EDisplayItemFilter.h"
#include "UI/BaseContentContainer.h"
#include "NewItemFilterContainer.generated.h"

UCLASS()
class DOMINIONPROTOCOL_API UNewItemFilterContainer : public UBaseContentContainer
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void SetCurrentItemFilter(const EDisplayItemFilter NewItemFilter);

	UFUNCTION()
	EDisplayItemFilter GetCurrentItemFilter() const { return CurrentItemFilter; }

protected:
	virtual void NativeConstruct() override;

	void BindInputActionDelegates();

	void BindChangeItemFilterFocusDelegates();

protected:
	UPROPERTY(BlueprintReadWrite)
	EDisplayItemFilter CurrentItemFilter;
};
