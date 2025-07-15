// Fill out your copyright notice in the Description page of Project Settings.


#include "NewMainMenuButtonContainer.h"

void UNewMainMenuButtonContainer::ChangeCurrentDisplaySubUI(const EDisplaySubMenuUI NewDisplaySubMenuUI)
{
	CurrentDisplaySubMenuUI = NewDisplaySubMenuUI;
	OnCurrentDisplaySubMenuUIChangedEvent.Broadcast(CurrentDisplaySubMenuUI);
}
