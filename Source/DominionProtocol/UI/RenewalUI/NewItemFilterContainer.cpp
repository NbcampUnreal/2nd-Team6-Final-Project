// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RenewalUI/NewItemFilterContainer.h"

#include "NewItemFilter.h"

void UNewItemFilterContainer::SetCurrentItemFilter(const EDisplayItemFilter NewItemFilter)
{
	CurrentItemFilter = NewItemFilter;
	OnCurrentItemFilterChangedEvent.Broadcast(CurrentItemFilter);
}

void UNewItemFilterContainer::NativeConstruct()
{
	Super::NativeConstruct();

	BindChangeItemFilterFocusDelegates();
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
