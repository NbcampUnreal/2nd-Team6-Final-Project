// Fill out your copyright notice in the Description page of Project Settings.


#include "NewMainMenuButtonContainer.h"

#include "Player/InGameController.h"

void UNewMainMenuButtonContainer::ChangeCurrentDisplaySubUI(const EDisplaySubMenuUI NewDisplaySubMenuUI)
{
	if (EDisplaySubMenuUI::Default == NewDisplaySubMenuUI)
	{
		CurrentDisplaySubMenuUI = EDisplaySubMenuUI::StatusMenu;
	}
	else
	{
		CurrentDisplaySubMenuUI = NewDisplaySubMenuUI;	
	}
	OnCurrentDisplaySubMenuUIChangedEvent.Broadcast(CurrentDisplaySubMenuUI);
}

void UNewMainMenuButtonContainer::NativeConstruct()
{
	Super::NativeConstruct();

	BindInputActionDelegates();

	ChangeFocusIndex(0);
}

void UNewMainMenuButtonContainer::BindInputActionDelegates()
{
	auto* InGameController = Cast<AInGameController>(GetOwningPlayer());
	if (InGameController)
	{
		InGameController->OnMainMenuUIMoveSelectionLeftEvent.AddUObject(this, &UNewMainMenuButtonContainer::DecreaseFocusIndex);
		InGameController->OnMainMenuUIMoveSelectionRightEvent.AddUObject(this, &UNewMainMenuButtonContainer::IncreaseFocusIndex);
	}
}
