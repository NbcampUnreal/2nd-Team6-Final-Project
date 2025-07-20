// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UITitle/NewTitleMenuButton.h"

#include "Components/SizeBox.h"
#include "Components/TextBlock.h"

void UNewTitleMenuButton::SetInfo()
{
	Super::SetInfo();
	
	Sizer->SetWidthOverride(Size.X);
	Sizer->SetHeightOverride(Size.Y);
	ButtonName->SetText(ButtonNameText);
}

void UNewTitleMenuButton::GetFocus()
{
	Super::GetFocus();

	SetFocus();
	GetFocusEffect();
}

void UNewTitleMenuButton::LoseFocus()
{
	Super::LoseFocus();
	
	LoseFocusEffect();
}

void UNewTitleMenuButton::BroadcastButtonClickEvent() const
{
	OnTitleMenuButtonClickedEvent.Broadcast();
}

void UNewTitleMenuButton::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetInfo();
}
