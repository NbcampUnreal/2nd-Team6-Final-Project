// Fill out your copyright notice in the Description page of Project Settings.


#include "NewMenuSelecter.h"

#include "NewMainMenuUI.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"

void UNewMenuSelecter::SetInfo()
{
	Super::SetInfo();

	if (Sizer)
	{
		Sizer->SetWidthOverride(Size.X);
		Sizer->SetHeightOverride(Size.Y);	
	}

	if (MenuSelecterName && SelecterName)
	{
		MenuSelecterName->SetText(SelecterNameText);
		SelecterName->SetText(SelecterNameText);
	}
}

void UNewMenuSelecter::GetFocus()
{
	Super::GetFocus();

	check(MainMenuUI);

	GetFocusEffects();
}

void UNewMenuSelecter::LoseFocus()
{
	Super::LoseFocus();

	check(MainMenuUI);
	
	LoseFocusEffects();
}

void UNewMenuSelecter::NativeConstruct()
{
	// 외부 참조가 필요없는 단순 데이터 입력이고, 디자인이 중요하기에 PreConstruct 에서 SetInfo() 실행
	// Super::NativeConstruct();
	
}

void UNewMenuSelecter::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetInfo();
}

