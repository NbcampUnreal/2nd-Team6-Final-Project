// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RenewalUI/NewSettingOptionContainer.h"

void UNewSettingOptionContainer::NativeConstruct()
{
	Super::NativeConstruct();

	GraphicSettingOptionArray.AddUnique(GraphicResolutionOption);
	GraphicSettingOptionArray.AddUnique(GraphicBrightnessOption);

	SoundSettingOptionArray.AddUnique(SoundMasterOption);
	SoundSettingOptionArray.AddUnique(SoundBGMOption);
	SoundSettingOptionArray.AddUnique(SoundEffectOption);
	SoundSettingOptionArray.AddUnique(SoundUIEffectsOption);
}
