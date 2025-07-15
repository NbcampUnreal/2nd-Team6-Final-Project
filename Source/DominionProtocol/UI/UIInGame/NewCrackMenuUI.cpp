// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIInGame/NewCrackMenuUI.h"

#include "NewCrackMenuButton.h"
#include "Player/InGameController.h"

UInputMappingContext* UNewCrackMenuUI::GetInputMappingContext_Implementation() const
{
	if (!CrackMenuUIMappingContext)
	{
		return nullptr;	
	}

	return CrackMenuUIMappingContext;
}

void UNewCrackMenuUI::NativeConstruct()
{
	Super::NativeConstruct();

	BindInputActionDelegates();
}

void UNewCrackMenuUI::BindInputActionDelegates()
{
	auto* InGameController = Cast<AInGameController>(GetOwningPlayer());
	if (InGameController)
	{
		InGameController->OnCrackMenuUIMoveSelectionUpEvent.AddUObject(this, &UNewCrackMenuUI::DecreaseFocusIndex);
		InGameController->OnCrackMenuUIMoveSelectionDownEvent.AddUObject(this, &UNewCrackMenuUI::IncreaseFocusIndex);
	}
}

