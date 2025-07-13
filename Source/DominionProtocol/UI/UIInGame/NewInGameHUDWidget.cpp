// Fill out your copyright notice in the Description page of Project Settings.


#include "NewInGameHUDWidget.h"


void UNewInGameHUDWidget::ActivateAlertUI()
{
	PushUI(AlertUI);
}

void UNewInGameHUDWidget::DeactivateAlertUI()
{
	PopSpecificUI(AlertUI);
}

void UNewInGameHUDWidget::ActivateCrackMenuUI()
{
	PushUI(CrackMenuUI);
}

void UNewInGameHUDWidget::DeactivateCrackMenuUI()
{
	PopSpecificUI(CrackMenuUI);
}

void UNewInGameHUDWidget::ActivateMainMenuUI()
{
	PushUI(MainMenuUI);
}

void UNewInGameHUDWidget::DeactivateMainMenuUI()
{
	PopSpecificUI(MainMenuUI);
}

void UNewInGameHUDWidget::ActivateDialogueUI()
{
	PushUI(DialogueUI);
}

void UNewInGameHUDWidget::DeactivateDialogueUI()
{
	PopSpecificUI(DialogueUI);
}

void UNewInGameHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ensureMsgf(StatusBarDisplay, TEXT("StatusBarDisplay is Null"));
	ensureMsgf(ItemSlotsDisplay, TEXT("ItemSlotsDisplay is Null"));
	ensureMsgf(InteractionDisplay, TEXT("InteractionDisplay is Null"));
	ensureMsgf(EventBoxDisplay, TEXT("EventBoxDisplay is Null"));
	ensureMsgf(BossMonsterHPBarDisplay, TEXT("BossMonsterHPBarDisplay is Null"));
	ensureMsgf(LockOnDisplay, TEXT("LockOnDisplay is Null"));
	ensureMsgf(AlertUI, TEXT("AlertUI is Null"));
	ensureMsgf(CrackMenuUI, TEXT("CrackMenuUI is Null"));
	ensureMsgf(MainMenuUI, TEXT("MainMenuUI is Null"));
	ensureMsgf(DialogueUI, TEXT("DialogueUI is Null"));

}




