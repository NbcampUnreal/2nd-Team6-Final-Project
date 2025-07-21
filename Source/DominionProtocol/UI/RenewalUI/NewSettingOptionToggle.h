// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/RenewalUI/NewSettingOption.h"
#include "NewSettingOptionToggle.generated.h"

UCLASS()
class DOMINIONPROTOCOL_API UNewSettingOptionToggle : public UNewSettingOption
{
	GENERATED_BODY()

public:
	void SetOptionInfo() const;
	
protected:
	UFUNCTION(BlueprintCallable)
	void DecreaseValueToggleOption();
	
	UFUNCTION(BlueprintCallable)
	void IncreaseValueToggleOption();

	virtual void NativePreConstruct() override;

protected:
	int32 CurrentValueIndex = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FText> SettingValueArray;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> SettingValueText;
};

