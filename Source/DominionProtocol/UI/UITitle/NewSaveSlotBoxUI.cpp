// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UITitle/NewSaveSlotBoxUI.h"

#include "NewSaveSlot.h"
#include "Components/VerticalBox.h"
#include "DomiFramework/GameInstance/SaveManagerSubsystem.h"
#include "EnumAndStruct/FCrackImageData.h"
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
			auto* NewSaveSlot = Cast<UNewSaveSlot>(Content);
			if (NewSaveSlot)
			{
				InputSaveSlotData(NewSaveSlot);
			}
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

void UNewSaveSlotBoxUI::InputSaveSlotData(UNewSaveSlot* SaveSlot) const
{
	
	if (!SaveManagerSubsystemInstance)
	{
		return; 
	}
	
	const TArray<FSaveSlotMetaData> SaveSlotArray = SaveManagerSubsystemInstance->GetSaveSlotArray();
	const int32 ContentIndex = SaveSlot->GetContentIndex();
	if (!SaveSlotArray.IsValidIndex(ContentIndex))
	{
		return;
	}
	
	const FSaveSlotMetaData SaveSlotMetaData = SaveSlotArray[ContentIndex];
	
	if (SaveSlotMetaData.SaveSlotExist)
	{
		UTexture2D* CrackMapImage = nullptr;
		FText CurrentCrackName = FText::GetEmpty();
		
		if (PastCrackImageDataTable && PresentCrackImageDataTable)
		{
			const FString SaveSlotCrackName = SaveSlotMetaData.RecentCrackName.ToString();

#pragma region SearchDataTable 
			auto SearchDataTable = [&](const UDataTable* DataTableToSearch) -> bool
			{
				if (!DataTableToSearch)
				{
					return false;
				}

				const TArray<FName> RowNames = DataTableToSearch->GetRowNames();
				for (const FName& RowName : RowNames)
				{
					FCrackImageData* FoundRow = DataTableToSearch->FindRow<FCrackImageData>(RowName, TEXT("SearchSingleDataTable"));
					if (FoundRow)
					{
						if (FoundRow->CrackDescription.ToString().Contains(SaveSlotCrackName))
						{
							CrackMapImage = FoundRow->CrackImageData;
							CurrentCrackName = SaveSlotMetaData.RecentCrackName;
							return true;
						}
					}
				}
				return false;
			};
#pragma endregion

			if (SearchDataTable(PastCrackImageDataTable))
			{
			}
			else if (SearchDataTable(PresentCrackImageDataTable))
			{
			}
		}

		const FString GameIndexString = FString::Printf(TEXT("게임 번호 %d"), SaveSlotMetaData.SaveSlotIndex+1);
		const FDateTime SaveDataTime = SaveSlotMetaData.SaveDateTime;
		const FString SaveTimeString = FString::Printf(TEXT("마지막 저장 시간 : %d / %d / %d : %d"), SaveDataTime.GetMonth(), SaveDataTime.GetDay(), SaveDataTime.GetHour(), SaveDataTime.GetMinute());
		const FString PlayTimeString = FString::Printf(TEXT("총 플레이 시간 : %d : %d"), SaveSlotMetaData.PlayTime/60, SaveSlotMetaData.PlayTime%60);
		const FText CurrentLevelName = SaveSlotMetaData.PlayingLevelDisplayName;
		const FString PlayerLevelString = FString::Printf(TEXT("플레이어 레벨 : %d"), SaveSlotMetaData.PlayerLevel);

		SaveSlot->SetInfo(SaveSlotMetaData.SaveSlotExist, CrackMapImage, GameIndexString,SaveTimeString ,PlayTimeString, CurrentCrackName, CurrentLevelName, PlayerLevelString);
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
