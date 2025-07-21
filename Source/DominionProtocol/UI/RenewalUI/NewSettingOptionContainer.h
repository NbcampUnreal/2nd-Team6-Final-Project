// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseContentContainer.h"
#include "NewSettingOptionContainer.generated.h"

class UNewSettingOption;

UCLASS()
class DOMINIONPROTOCOL_API UNewSettingOptionContainer : public UBaseContentContainer
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY()
	TArray<TObjectPtr<UNewSettingOption>> GraphicSettingOptionArray;
	
	UPROPERTY()
	TArray<TObjectPtr<UNewSettingOption>> SoundSettingOptionArray;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UNewSettingOption> GraphicResolutionOption;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UNewSettingOption> GraphicBrightnessOption;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UNewSettingOption> SoundMasterOption;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UNewSettingOption> SoundBGMOption;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UNewSettingOption> SoundEffectOption;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UNewSettingOption> SoundUIEffectsOption;
};
