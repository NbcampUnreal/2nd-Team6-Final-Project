// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RenewalUI/NewMainMenuUI.h"

#include "NewMainMenuButtonContainer.h"
#include "NewMainMenuSubUIContainer.h"

UInputMappingContext* UNewMainMenuUI::GetInputMappingContext_Implementation() const
{
	if (!MainMenuUIMappingContext)
	{
		return nullptr;
	}
	
	return MainMenuUIMappingContext;
}

void UNewMainMenuUI::NativeConstruct()
{
	Super::NativeConstruct();

	BindMainMenuSubUIAndMainMenuButtonContainer();
}

void UNewMainMenuUI::BindMainMenuSubUIAndMainMenuButtonContainer() const
{
	auto* MainMenuSubUI = Cast<UNewMainMenuSubUIContainer>(MainMenuSubUIContainer);
	if (MainMenuSubUI)
	{
		auto* ButtonContainer = Cast<UNewMainMenuButtonContainer>(MainMenuButtonContainer);
		if (ButtonContainer)
		{
			MainMenuSubUI->SetMainMenuButtonContainer(ButtonContainer);
			MainMenuSubUI->BindDisplaySubUIChangedDelegate();
		}
	}
}
