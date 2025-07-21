// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RenewalUI/NewSettingOptionEditable.h"

#include "Components/EditableText.h"


void UNewSettingOptionEditable::SetOptionInfo(const FText& NewValue) const
{
	if (NewValue.IsNumeric())
	{
		const int32 NewValueInt = FCString::Atoi(*NewValue.ToString());
		const int32 ClampedValue = FMath::Clamp(NewValueInt, 0, 100);
		SettingValueText->SetText(FText::AsNumber(ClampedValue));
	}
	else
	{
		SettingValueText->SetText(NewValue);
	}
}

void UNewSettingOptionEditable::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetOptionInfo(SettingOptionValue);
}

void UNewSettingOptionEditable::DecreaseValueEditableOption()
{
	if (SettingOptionValue.IsNumeric())
	{
		int32 NewValueInt = FCString::Atoi(*SettingOptionValue.ToString());
		if (NewValueInt > 0)
		{
			NewValueInt = NewValueInt - ButtonMultiply;
			SettingOptionValue = FText::AsNumber(NewValueInt);
			SetOptionInfo(SettingOptionValue);
		}
	}
}

void UNewSettingOptionEditable::IncreaseValueEditableOption()
{
	if (SettingOptionValue.IsNumeric())
	{
		int32 NewValueInt = FCString::Atoi(*SettingOptionValue.ToString());
		if (NewValueInt < 100)
		{
			NewValueInt = NewValueInt + ButtonMultiply;
			SettingOptionValue = FText::AsNumber(NewValueInt);
			SetOptionInfo(SettingOptionValue);
		}
	}
}
