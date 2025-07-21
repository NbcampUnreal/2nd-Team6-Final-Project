// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RenewalUI/NewSettingMenu.h"

#include "Components/TextBlock.h"

void UNewSettingMenu::SetInfo()
{
	Super::SetInfo();

	SettingButtonName->SetText(SettingMenuNameText);
}

void UNewSettingMenu::GetFocus()
{
	Super::GetFocus();

	OnGetFocusSettingMenuEvent.Broadcast(this);
	
	GetFocusEffects();
}

void UNewSettingMenu::LoseFocus()
{
	Super::LoseFocus();

	OnLoseFocusSettingMenuEvent.Broadcast(this);

	LoseFocusEffects();
}

void UNewSettingMenu::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetInfo();
}
