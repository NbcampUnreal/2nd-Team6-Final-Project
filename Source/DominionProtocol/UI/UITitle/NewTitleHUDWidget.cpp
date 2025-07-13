// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UITitle/NewTitleHUDWidget.h"

#include "Player/TitleController.h"

void UNewTitleHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	ensureMsgf(TitleMenuUI, TEXT("TitleMenuUI Not Connected"));
	ensureMsgf(SaveSlotBoxUI, TEXT("SaveSlotBoxUI Not Connected"));
	
	auto* PlayerController = Cast<ATitleController>(GetOwningPlayer());
	if (PlayerController)
	{
		TitleController = PlayerController;
	}
	
	BindTopUIChangeDelegate();

	PushUI(TitleMenuUI);
}

void UNewTitleHUDWidget::ActivateSaveSlotUI()
{
	PushUI(SaveSlotBoxUI);
}

void UNewTitleHUDWidget::DeactivateSaveSlotUI()
{
	PopSpecificUI(SaveSlotBoxUI);
}
