// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RenewalUI/NewItemFilterContainer.h"

#include "NewItemFilter.h"
#include "Player/InGameController.h"

void UNewItemFilterContainer::SetCurrentItemFilter(const EDisplayItemFilter NewItemFilter)
{
	CurrentItemFilter = NewItemFilter;
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

void UNewItemFilterContainer::BindChangeItemFilterFocusDelegates()
{
	if (ContentArray.Num() > 0)
	{
		for (UBaseContent* Content : ContentArray)
		{
			auto* ItemFilter = Cast<UNewItemFilter>(Content);
			if (ItemFilter)
			{
				ItemFilter->OnChangeItemFilterFocusEvent.AddUObject(this, &UNewItemFilterContainer::SetCurrentItemFilter);
			}
		}
	}
}
