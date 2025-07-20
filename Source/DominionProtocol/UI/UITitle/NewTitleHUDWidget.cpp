// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UITitle/NewTitleHUDWidget.h"

#include "NewSaveSlotContainerUI.h"
#include "NewTitleMenuButton.h"
#include "NewTitleMenuUI.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Player/TitleController.h"
#include "UI/RenewalUI/NewShotcutButton.h"

void UNewTitleHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	ensureMsgf(TitleMenuUI, TEXT("TitleMenuUI Not Connected"));
	ensureMsgf(SaveSlotContainerUI, TEXT("SaveSlotBoxUI Not Connected"));

	BindButtonActionDelegates();
	BindInputActionDelegates();
	
	PushUI(TitleMenuUI);
}

void UNewTitleHUDWidget::ActivateSaveSlotUI()
{
	PushUI(SaveSlotContainerUI);
}

void UNewTitleHUDWidget::DeactivateSaveSlotUI()
{
	PopSpecificUI(SaveSlotContainerUI);
}

void UNewTitleHUDWidget::ExitGame() const
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, false);
}


void UNewTitleHUDWidget::BindButtonActionDelegates()
{
	auto* NewTitleMenuUI = Cast<UNewTitleMenuUI>(TitleMenuUI);
	if (NewTitleMenuUI)
	{
		UNewTitleMenuButton* StartGameButton = NewTitleMenuUI->GetStartGameButton();
		if (StartGameButton)
		{
			StartGameButton->OnTitleMenuButtonClickedEvent.AddUObject(this, &UNewTitleHUDWidget::ActivateSaveSlotUI);
		}

		UNewTitleMenuButton* ExitGameButton = NewTitleMenuUI->GetExitGameButton();
		if (ExitGameButton)
		{
			ExitGameButton->OnTitleMenuButtonClickedEvent.AddUObject(this, &UNewTitleHUDWidget::ExitGame);
		}
	}

	auto* NewSaveSlotContainerUI = Cast<UNewSaveSlotContainerUI>(SaveSlotContainerUI);
	if (NewSaveSlotContainerUI)
	{
		UNewShotcutButton* BackButton = NewSaveSlotContainerUI->GetBackButton();
		if (BackButton)
		{
			BackButton->OnShotcutButtonClickedEvent.AddUObject(this, &UNewTitleHUDWidget::DeactivateSaveSlotUI);
		}
	}
}

void UNewTitleHUDWidget::BindInputActionDelegates()
{
	auto* TitleController = Cast<ATitleController>(GetOwningPlayer());
	if (TitleController)
	{
		TitleController->OnSlotUIBackToTitleMenuEvent.AddUObject(this, &UNewTitleHUDWidget::DeactivateSaveSlotUI);	
	}
}
