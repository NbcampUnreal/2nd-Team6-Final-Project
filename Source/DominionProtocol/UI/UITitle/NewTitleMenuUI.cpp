// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UITitle/NewTitleMenuUI.h"

#include "Components/VerticalBox.h"
#include "Player/TitleController.h"
#include "UI/UITitle/NewTitleMenuButton.h"

void UNewTitleMenuUI::NativeConstruct()
{
	Super::NativeConstruct();

	BindInputActionDelegates();
}

UInputMappingContext* UNewTitleMenuUI::GetInputMappingContext_Implementation() const
{
	return TitleMenuMappingContext;
}

void UNewTitleMenuUI::OnConfirmSelection() const
{
	if (ContentArray.Num() > 0)
	{
		if (ContentArray.IsValidIndex(CurrentFocusIndex))
		{
			const auto* TitleMenuButton = Cast<UNewTitleMenuButton>(ContentArray[CurrentFocusIndex]);
			if (TitleMenuButton)
			{
				TitleMenuButton->BroadcastButtonClickEvent();
			}
		}
	}
}

void UNewTitleMenuUI::BindInputActionDelegates()
{
	auto* TitleController = Cast<ATitleController>(GetOwningPlayer());
	if (TitleController)
	{
		TitleController->OnMenuUIMoveSelectionUpEvent.AddUObject(this, &UNewTitleMenuUI::DecreaseFocusIndex);
		TitleController->OnMenuUIMoveSelectionDownEvent.AddUObject(this, &UNewTitleMenuUI::IncreaseFocusIndex);
		TitleController->OnMenuUIConfirmSelectionEvent.AddUObject(this, &UNewTitleMenuUI::OnConfirmSelection);
	}
}
