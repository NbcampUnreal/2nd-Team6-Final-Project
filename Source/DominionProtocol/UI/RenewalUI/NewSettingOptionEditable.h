// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/RenewalUI/NewSettingOption.h"
#include "NewSettingOptionEditable.generated.h"

class UEditableText;

UCLASS()
class DOMINIONPROTOCOL_API UNewSettingOptionEditable : public UNewSettingOption
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetOptionInfo(const FText& NewValue) const;

protected:
	UFUNCTION(BlueprintCallable)
	void DecreaseValueEditableOption();

	UFUNCTION(BlueprintCallable)
	void IncreaseValueEditableOption();

	virtual void NativePreConstruct() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ButtonMultiply = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText SettingOptionValue;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UEditableText> SettingValueText;
};