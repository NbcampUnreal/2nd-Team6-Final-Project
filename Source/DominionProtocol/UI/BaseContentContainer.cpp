// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseContentContainer.h"

#include "BaseContent.h"
#include "Components/PanelWidget.h"

void UBaseContentContainer::ChangeFocusIndex(const int32 NewFocusIndex)
{
	for (int32 i = 0; i < ContentArray.Num(); i++)
	{
		if (i == NewFocusIndex)
		{
			ContentArray[i]->GetFocus();
			CurrentFocusIndex = NewFocusIndex;
			OnFocusIndexChanged.Broadcast(NewFocusIndex);
		}
		else
		{
			ContentArray[i]->LoseFocus();
		}
	}
}

void UBaseContentContainer::IncreaseFocusIndex()
{
	if (CurrentFocusIndex >= MaxFocusIndex)
	{
		return;
	}

	ChangeFocusIndex(CurrentFocusIndex + 1);
}

void UBaseContentContainer::DecreaseFocusIndex()
{
	if (CurrentFocusIndex <= 0)
	{
		return;
	}

	ChangeFocusIndex(CurrentFocusIndex - 1);
}

void UBaseContentContainer::NativeConstruct()
{
	Super::NativeConstruct();

	if (ContentContainer)
	{
		const TArray<UWidget*> Widgets  = ContentContainer->GetAllChildren();
		if (Widgets.Num() > 0)
		{
			for (int32 i = 0; i < Widgets.Num(); i++)
			{
				auto* ContentWidget = Cast<UBaseContent>(Widgets[i]);
				if (ContentWidget)
				{
					ContentWidget->SetContentIndex(i);
					ContentArray.AddUnique(ContentWidget);
				}
			}
		}
	}
	
	MaxFocusIndex = ContentArray.Num() - 1;
	CurrentFocusIndex = 0;
}
