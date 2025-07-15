// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UITitle/NewSaveSlotBoxUI.h"

#include "Components/VerticalBox.h"
#include "DomiFramework/GameInstance/SaveManagerSubsystem.h"
#include "Player/TitleController.h"
#include "UI/BaseContent.h"

UInputMappingContext* UNewSaveSlotBoxUI::GetInputMappingContext_Implementation() const
{
	return TitleSlotUIMappingContext;
}

void UNewSaveSlotBoxUI::RefreshSlotData(const ESlateVisibility VisibilityState)
{
	if (VisibilityState == ESlateVisibility::Visible)
	{
		for (UBaseContent* Content : ContentArray)
		{
			Content->SetInfo();
		}	
	}
}

void UNewSaveSlotBoxUI::OnMoveSelectionUp()
{
	DecreaseFocusIndex();
}

void UNewSaveSlotBoxUI::OnMoveSelectionDown()
{
	IncreaseFocusIndex();
}

void UNewSaveSlotBoxUI::StartGame() const
{
	// SlotIndex는 위젯에서 설정
	if (CurrentFocusIndex != -1)
	{
		auto* TitleController = Cast<ATitleController>(GetOwningPlayer());
		check(TitleController);
		TitleController->FadeOut();

		int32 SlotIndexToUseTimer = CurrentFocusIndex;
		
		FTimerHandle FadeTimerHandle;
		TWeakObjectPtr WeakThis = this;
		GetWorld()->GetTimerManager().SetTimer(
			FadeTimerHandle,
			[WeakThis, SlotIndexToUseTimer]()
			{
				if (WeakThis.IsValid())
				{
					check(WeakThis->GetSaveManagerSubsystemInstance());
					WeakThis->GetSaveManagerSubsystemInstance()->StartNewGame(SlotIndexToUseTimer);	
				}
			},
			TitleController->GetFadeDuration() + 0.1f,
			false
			);
	}
}

void UNewSaveSlotBoxUI::LoadGame() const
{
	if (CurrentFocusIndex != -1)
	{
		auto* TitleController = Cast<ATitleController>(GetOwningPlayer());
		check(TitleController);
		TitleController->FadeOut();

		int32 SlotIndexToUseTimer = CurrentFocusIndex;

		FTimerHandle FadeTimerHandle;
		TWeakObjectPtr WeakThis = this;
		GetWorld()->GetTimerManager().SetTimer(
			FadeTimerHandle,
			[WeakThis, SlotIndexToUseTimer]()
			{
				if (WeakThis.IsValid())
				{
					check(WeakThis->GetSaveManagerSubsystemInstance());
					WeakThis->GetSaveManagerSubsystemInstance()->LoadSaveDataAndOpenLevel(SlotIndexToUseTimer);	
				}
			},
			TitleController->GetFadeDuration() + 0.1f,
			false
			);
	}
}

void UNewSaveSlotBoxUI::DeleteGame()
{
	if (CurrentFocusIndex != -1)
	{
		SaveManagerSubsystemInstance->DeleteSaveSlot(CurrentFocusIndex);
		RefreshSlotData(ESlateVisibility::Visible);
	}
}

void UNewSaveSlotBoxUI::NativeConstruct()
{
	Super::NativeConstruct();

	const auto* GameInstance = GetWorld()->GetGameInstance();
	auto* SaveManagerSubsystem = GameInstance->GetSubsystem<USaveManagerSubsystem>();
	
	ensureMsgf(SaveManagerSubsystem, TEXT("Casting failed to SaveManagerSubsystem in UNewSettingWidget"));
	
	if (SaveManagerSubsystem)
	{
		SaveManagerSubsystemInstance = SaveManagerSubsystem;
	}

	
	
	BindInputActionDelegates();

	OnVisibilityChanged.AddDynamic(this, &UNewSaveSlotBoxUI::RefreshSlotData);
}

void UNewSaveSlotBoxUI::BindInputActionDelegates()
{
	auto* TitleController = Cast<ATitleController>(GetOwningPlayer());
	if (TitleController)
	{
		TitleController->OnSlotUIStartGameEvent.AddUObject(this, &UNewSaveSlotBoxUI::OnStartGame);
		TitleController->OnSlotUIDeleteGameEvent.AddUObject(this, &UNewSaveSlotBoxUI::OnDeleteGame);
		TitleController->OnSlotUIBackToTitleMenuEvent.AddUObject(this, &UNewSaveSlotBoxUI::OnBackToTitleMenu);
		TitleController->OnSlotUIMoveSelectionUpEvent.AddUObject(this, &UNewSaveSlotBoxUI::OnMoveSelectionUp);
		TitleController->OnSlotUIMoveSelectionDownEvent.AddUObject(this, &UNewSaveSlotBoxUI::OnMoveSelectionDown);
	}
}
