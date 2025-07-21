// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RenewalUI/NewSettingOptionToggle.h"

#include "Components/TextBlock.h"

void UNewSettingOptionToggle::SetOptionInfo() const
{
	if (SettingValueArray.IsValidIndex(CurrentValueIndex))
	{
		SettingValueText->SetText(SettingValueArray[CurrentValueIndex]);	
	}
}

void UNewSettingOptionToggle::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetOptionInfo();
}

void UNewSettingOptionToggle::DecreaseValueToggleOption()
{
	if (SettingValueArray.Num() == 0)
	{
		return;
	}

	if (CurrentValueIndex > 0)
	{
		CurrentValueIndex--;

		SetOptionInfo();
	}
}

void UNewSettingOptionToggle::IncreaseValueToggleOption()
{
	if (SettingValueArray.Num() == 0)
	{
		return;
	}

	if (CurrentValueIndex < SettingValueArray.Num() - 1)
	{
		CurrentValueIndex++;
		
		SetOptionInfo();
	}
}
