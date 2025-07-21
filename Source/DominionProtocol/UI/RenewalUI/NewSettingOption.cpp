// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RenewalUI/NewSettingOption.h"

#include "Components/TextBlock.h"

void UNewSettingOption::GetFocus()
{
	Super::GetFocus();

	GetEffects();
}

void UNewSettingOption::LoseFocus()
{
	Super::LoseFocus();

	LoseEffects();
}

void UNewSettingOption::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	SettingOptionNameText->SetText(SettingOptionName);
}
