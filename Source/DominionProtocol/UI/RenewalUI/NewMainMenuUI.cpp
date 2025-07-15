// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RenewalUI/NewMainMenuUI.h"

#include "NewMainMenuButtonContainer.h"
#include "NewMainMenuSubUIContainer.h"

void UNewMainMenuUI::NativeConstruct()
{
	Super::NativeConstruct();

	auto* MainMenuSubUI = Cast<UNewMainMenuSubUIContainer>(MainMenuSubUIContainer);
	if (MainMenuSubUI)
	{
		auto* ButtonContainer = Cast<UNewMainMenuButtonContainer>(MainMenuButtonContainer);
		if (ButtonContainer)
		{
			MainMenuSubUI->SetMainMenuButtonContainer(ButtonContainer);	
		}
	}
}
