// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UITitle/NewSaveSlotContainerUI.h"

#include "NewSaveSlot.h"
#include "Components/VerticalBox.h"
#include "DomiFramework/GameInstance/SaveManagerSubsystem.h"
#include "EnumAndStruct/FCrackImageData.h"
#include "Player/TitleController.h"
#include "UI/BaseContent.h"
#include "UI/RenewalUI/NewShotcutButton.h"

UInputMappingContext* UNewSaveSlotContainerUI::GetInputMappingContext_Implementation() const
{
	return TitleSlotUIMappingContext;
}

void UNewSaveSlotContainerUI::RefreshSlotData(const ESlateVisibility VisibilityState)
{
	if (VisibilityState == ESlateVisibility::Visible)
	{
		for (UBaseContent* Content : ContentArray)
		{
			auto* NewSaveSlot = Cast<UNewSaveSlot>(Content);
			if (NewSaveSlot)
			{
				SetSaveSlotData(NewSaveSlot);
			}
		}	
	}
}

void UNewSaveSlotContainerUI::OnStartGame()
{
	if (ContentArray.IsValidIndex(CurrentFocusIndex))
	{
		const auto* SaveSlot = Cast<UNewSaveSlot>(ContentArray[CurrentFocusIndex]);
		if (SaveSlot)
		{
			if (!SaveSlot->GetExistSaveSlotData())
			{
				StartGame();
				return;
			}
			LoadGame();
		}
	}
}

void UNewSaveSlotContainerUI::OnDeleteGame()
{
	if (ContentArray.IsValidIndex(CurrentFocusIndex))
	{
		const auto* SaveSlot = Cast<UNewSaveSlot>(ContentArray[CurrentFocusIndex]);
		if (SaveSlot)
		{
			if (!SaveSlot->GetExistSaveSlotData())
			{
				return;
			}
			DeleteGame();
		}
	}
}

void UNewSaveSlotContainerUI::StartGame() const
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

void UNewSaveSlotContainerUI::LoadGame() const
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

void UNewSaveSlotContainerUI::DeleteGame()
{
	if (CurrentFocusIndex == -1)
	{
		return;
	}
	
	SaveManagerSubsystemInstance->DeleteSaveSlot(CurrentFocusIndex);
	RefreshSlotData(ESlateVisibility::Visible);
}

void UNewSaveSlotContainerUI::SetSaveSlotData(UNewSaveSlot* SaveSlot) const
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
	else
	{
		SaveSlot->SetInfoEmpty();
	}
}

void UNewSaveSlotContainerUI::NativeConstruct()
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
	BindButtonActionDelegates();

	OnVisibilityChanged.AddDynamic(this, &UNewSaveSlotContainerUI::RefreshSlotData);
}

void UNewSaveSlotContainerUI::BindInputActionDelegates()
{
	auto* TitleController = Cast<ATitleController>(GetOwningPlayer());
	if (TitleController)
	{
		TitleController->OnSlotUIStartGameEvent.AddUObject(this, &UNewSaveSlotContainerUI::OnStartGame);
		TitleController->OnSlotUIDeleteGameEvent.AddUObject(this, &UNewSaveSlotContainerUI::OnDeleteGame);
		TitleController->OnSlotUIMoveSelectionUpEvent.AddUObject(this, &UNewSaveSlotContainerUI::DecreaseFocusIndex);
		TitleController->OnSlotUIMoveSelectionDownEvent.AddUObject(this, &UNewSaveSlotContainerUI::IncreaseFocusIndex);
	}
}

void UNewSaveSlotContainerUI::BindButtonActionDelegates()
{
	if (StartButton)
	{
		StartButton->OnShotcutButtonClickedEvent.AddUObject(this, &UNewSaveSlotContainerUI::OnStartGame);
	}

	if (DeleteButton)
	{
		DeleteButton->OnShotcutButtonClickedEvent.AddUObject(this, &UNewSaveSlotContainerUI::OnDeleteGame);
	}

	if (ContentArray.Num() > 0)
	{
		for (UBaseContent* Content : ContentArray)
		{
			auto* SaveSlot = Cast<UNewSaveSlot>(Content);
			if (SaveSlot)
			{
				SaveSlot->OnButtonClickedEvent.AddUObject(this, &UNewSaveSlotContainerUI::OnStartGame);
			}
		}
	}
}
