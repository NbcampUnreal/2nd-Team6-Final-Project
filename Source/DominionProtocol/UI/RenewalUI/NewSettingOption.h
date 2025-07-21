// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseContent.h"
#include "NewSettingOption.generated.h"

class UTextBlock;

UCLASS()
class DOMINIONPROTOCOL_API UNewSettingOption : public UBaseContent
{
	GENERATED_BODY()

public:
	virtual void GetFocus() override;

	virtual void LoseFocus() override;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void GetEffects();

	UFUNCTION(BlueprintImplementableEvent)
	void LoseEffects();
	
	virtual void NativePreConstruct() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText SettingOptionName;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> SettingOptionNameText;

};

