// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnumAndStruct/EDisplayItemFilter.h"
#include "UI/BaseContent.h"
#include "NewItemFilter.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnChangeItemFilterFocusEvent, EDisplayItemFilter)

class UImage;

UCLASS()
class DOMINIONPROTOCOL_API UNewItemFilter : public UBaseContent
{
	GENERATED_BODY()

public:
	FOnChangeItemFilterFocusEvent OnChangeItemFilterFocusEvent;
	
	virtual void SetInfo() override;

	virtual void GetFocus() override;
	
	virtual void LoseFocus() override;

protected:
	virtual void NativePreConstruct() override;

	UFUNCTION(BlueprintImplementableEvent)
	void GetFocusEffects();
	
	UFUNCTION(BlueprintImplementableEvent)
	void LoseFocusEffects();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UTexture2D> IconTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDisplayItemFilter ItemFilter;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UImage> ItemFilterImage;
};
