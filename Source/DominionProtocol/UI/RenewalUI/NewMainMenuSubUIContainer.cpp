// Fill out your copyright notice in the Description page of Project Settings.


#include "NewMainMenuSubUIContainer.h"

#include "NewMainMenuButtonContainer.h"

void UNewMainMenuSubUIContainer::ChangeDisplaySubUI(const EDisplaySubMenuUI NewDisplaySubMenuUI)
{
	const int32 DisplaySubUIIndex = static_cast<int32>(NewDisplaySubMenuUI);
	if (DisplaySubUIIndex >= SubUIArray.Num())
	{
		return;
	}
	
	PushUI(SubUIArray[DisplaySubUIIndex]);
}

void UNewMainMenuSubUIContainer::NativeConstruct()
{
	Super::NativeConstruct();

	SubUIArray.AddUnique(StatusSubUI);
	SubUIArray.AddUnique(EquipmentSubUI);
	SubUIArray.AddUnique(ItemSubUI);
	SubUIArray.AddUnique(SettingSubUI);

	BindDisplaySubUIChangedDelegate();
}

void UNewMainMenuSubUIContainer::BindDisplaySubUIChangedDelegate()
{
	MainMenuButtonContainer->OnCurrentDisplaySubMenuUIChangedEvent.AddUObject(this, &UNewMainMenuSubUIContainer::ChangeDisplaySubUI);
}
