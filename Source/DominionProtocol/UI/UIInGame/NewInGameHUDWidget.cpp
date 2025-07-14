// Fill out your copyright notice in the Description page of Project Settings.


#include "NewInGameHUDWidget.h"

#include "NewAlertUI.h"
#include "NewDialogueUI.h"
#include "Kismet/GameplayStatics.h"
#include "Player/InGameController.h"
#include "WorldObjects/BlockedPath.h"
#include "WorldObjects/DialogueManager.h"
#include "WorldObjects/DyingHelper.h"
#include "WorldObjects/Crack.h"
#include "WorldObjects/BossSpawner.h"


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

	BindInputActionDelegates();
	BindCreateDialogueDelegate();
	BindDialogueTypingFinishedDelegate();
	BindAlertDisplayFinishedDelegate();
}

void UNewInGameHUDWidget::BindInputActionDelegates()
{
	auto* InGameController = Cast<AInGameController>(GetOwningPlayer());
	if (InGameController)
	{
		InGameController->OnMainMenuUIActivateActionEvent.AddUObject(this, &UNewInGameHUDWidget::ActivateMainMenuUI);
		InGameController->OnMainMenuUIDeactivateActionEvent.AddUObject(this, &UNewInGameHUDWidget::DeactivateMainMenuUI);
	}
}

void UNewInGameHUDWidget::BindCreateDialogueDelegate()
{
	BindDialogueSources<ACrack>();
	BindDialogueSources<ABlockedPath>();
	BindDialogueSources<ADyingHelper>();
	BindDialogueSources<ABossSpawner>();
}

template<typename T>
void UNewInGameHUDWidget::BindDialogueSources()
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), T::StaticClass(), Actors);

	for (const auto Actor : Actors)
	{
		if (T* TypedActor = Cast<T>(Actor))
		{
			TypedActor->OnCreateDialogueManager.AddUObject(this, &UNewInGameHUDWidget::BindActivateDialogueDelegate);
		}
	}
}

void UNewInGameHUDWidget::BindActivateDialogueDelegate(UDialogueManager* DialogueManager)
{
	DialogueManager->OnActivateDialogueUIEvent.Clear();
	DialogueManager->OnActivateDialogueUIEvent.AddUObject(this, &UNewInGameHUDWidget::ActivateDialogueUI);
}

void UNewInGameHUDWidget::BindDialogueTypingFinishedDelegate()
{
	if (DialogueUI)
	{
		auto* NewDialogueUI = Cast<UNewDialogueUI>(DialogueUI);
		if (NewDialogueUI)
		{
			NewDialogueUI->OnDialogueTypingFinishedEvent.AddUObject(this, &UNewInGameHUDWidget::DeactivateDialogueUI);
		}
	}
}

void UNewInGameHUDWidget::BindAlertDisplayFinishedDelegate()
{
	if (AlertUI)
	{
		auto* NewAlertUI = Cast<UNewAlertUI>(AlertUI);
		if (NewAlertUI)
		{
			NewAlertUI->OnAlertDisplayFinishedEvent.AddUObject(this, &UNewInGameHUDWidget::DeactivateAlertUI);
		}
	}
}




