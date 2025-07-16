// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RenewalUI/NewItemFilterContainer.h"

#include "Player/InGameController.h"

void UNewItemFilterContainer::SetCurrentItemFilter(const EDisplayItemFilter NewItemFilter)
{
	CurrentItemFilter = NewItemFilter;
	OnDisplayItemFilterChangedEvent.Broadcast(CurrentItemFilter);
}

void UNewItemFilterContainer::NativeConstruct()
{
	Super::NativeConstruct();
	
	BindInputActionDelegates();
}

void UNewItemFilterContainer::BindInputActionDelegates()
{
	auto* InGameController = Cast<AInGameController>(GetOwningPlayer());
	if (InGameController)
	{
		InGameController->OnItemUIMoveSelectionLeftEvent.AddUObject(this, &UNewItemFilterContainer::DecreaseFocusIndex);
		InGameController->OnItemUIMoveSelectionRightEvent.AddUObject(this, &UNewItemFilterContainer::IncreaseFocusIndex);
	}
}
