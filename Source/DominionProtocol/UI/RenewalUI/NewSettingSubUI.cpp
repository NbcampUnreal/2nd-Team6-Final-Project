// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RenewalUI/NewSettingSubUI.h"

#include "NewSettingMenu.h"
#include "NewSettingMenuContainer.h"
#include "NewSettingOption.h"
#include "NewSettingOptionContainer.h"
#include "DomiFramework/GameInstance/SoundInstanceSubsystem.h"
#include "Player/InGameController.h"


void UNewSettingSubUI::NativeConstruct()
{
	Super::NativeConstruct();

	const auto* GameInstance = GetWorld()->GetGameInstance();
	auto* SoundSubsystem = GameInstance->GetSubsystem<USoundInstanceSubsystem>();
	
	ensureMsgf(SoundSubsystem, TEXT("Casting failed to SoundSubsystem in UNewSettingWidget"));
	
	if (SoundSubsystem)
	{
		SoundSubsystemInstance = SoundSubsystem;
	}

	BindInputActionDelegates();
	BindFocusSettingMenuChangedDelegates();
}

void UNewSettingSubUI::ApplyMasterVolumeValue(const float NewVolumeValue)
{
	if (SoundSubsystemInstance)
	{
		MasterVolumeValue = NewVolumeValue;
		SoundSubsystemInstance->SetMasterVolume(NewVolumeValue);
	}
}

void UNewSettingSubUI::ApplyBackgroundMusicVolumeValue(const float NewVolumeValue)
{
	if (SoundSubsystemInstance)
	{
		BackgroundMusicVolumeValue = NewVolumeValue;
		SoundSubsystemInstance->SetBGMVolume(NewVolumeValue);
	}
}

void UNewSettingSubUI::ApplySoundEffectsVolumeValue(const float NewVolumeValue)
{
	if (SoundSubsystemInstance)
	{
		SoundEffectsVolumeValue = NewVolumeValue;
		SoundSubsystemInstance->SetSFXVolume(NewVolumeValue);
	}
}

void UNewSettingSubUI::ApplyUIEffectsVolumeValue(const float NewVolumeValue)
{
	if (SoundSubsystemInstance)
	{
		UIEffectsVolumeValue = NewVolumeValue;
		SoundSubsystemInstance->SetUIVolume(NewVolumeValue);
	}
}

void UNewSettingSubUI::BindInputActionDelegates()
{
	auto* InGameController = Cast<AInGameController>(GetOwningPlayer());
	if (InGameController)
	{
		InGameController->OnSettingUIMoveSelectionUpEvent.AddUObject(SettingMenuContainer, &UNewSettingMenuContainer::DecreaseFocusIndex);
		InGameController->OnSettingUIMoveSelectionDownEvent.AddUObject(SettingMenuContainer, &UNewSettingMenuContainer::IncreaseFocusIndex);
	}
}

void UNewSettingSubUI::BindFocusSettingMenuChangedDelegates()
{
	SettingMenuContainer->GetGraphicSettingButton()->OnGetFocusSettingMenuEvent.AddUObject(this, &UNewSettingSubUI::ShowSettingOption);
	SettingMenuContainer->GetGraphicSettingButton()->OnLoseFocusSettingMenuEvent.AddUObject(this, &UNewSettingSubUI::HideSettingOption);
	SettingMenuContainer->GetSoundSettingButton()->OnGetFocusSettingMenuEvent.AddUObject(this, &UNewSettingSubUI::ShowSettingOption);
	SettingMenuContainer->GetSoundSettingButton()->OnLoseFocusSettingMenuEvent.AddUObject(this, &UNewSettingSubUI::HideSettingOption);
}

void UNewSettingSubUI::SetMasterVolumeValue(const float NewVolumeValue)
{
	if (SoundSubsystemInstance)
	{
		DesiredMasterVolumeValue = NewVolumeValue;
		SoundSubsystemInstance->SetMasterVolume(NewVolumeValue);
	}
}

void UNewSettingSubUI::SetBackgroundMusicVolumeValue(const float NewVolumeValue)
{
	if (SoundSubsystemInstance)
	{
		DesiredBackgroundMusicVolumeValue = NewVolumeValue;
		SoundSubsystemInstance->SetBGMVolume(NewVolumeValue);
	}
}

void UNewSettingSubUI::SetSoundEffectsVolumeValue(const float NewVolumeValue)
{
	if (SoundSubsystemInstance)
	{
		DesiredSoundEffectsVolumeValue = NewVolumeValue;
		SoundSubsystemInstance->SetSFXVolume(NewVolumeValue);
	}
}

void UNewSettingSubUI::SetUIEffectsVolumeValue(const float NewVolumeValue)
{
	if (SoundSubsystemInstance)
	{
		DesiredUIEffectsVolumeValue = NewVolumeValue;
		SoundSubsystemInstance->SetUIVolume(NewVolumeValue);
	}
}

UInputMappingContext* UNewSettingSubUI::GetInputMappingContext_Implementation() const
{
	if (!SettingSubUIMappingContext)
	{
		return nullptr;	
	}

	return SettingSubUIMappingContext;
}

void UNewSettingSubUI::ShowSettingOption(UNewSettingMenu* SettingMenu) const
{
	const UNewSettingMenu* GraphicMenu = SettingMenuContainer->GetGraphicSettingButton();
	if (SettingMenu == GraphicMenu)
	{
		const TArray<UNewSettingOption*> GraphicOptionArray = SettingOptionContainer->GetGraphicSettingOptionArray();
		if (GraphicOptionArray.Num() > 0)
		{
			for (UNewSettingOption* GraphicOption : GraphicOptionArray)
			{
				GraphicOption->SetVisibility(ESlateVisibility::Visible);
			}
		}
	}

	const UNewSettingMenu* SoundMenu = SettingMenuContainer->GetSoundSettingButton();
	if (SettingMenu == SoundMenu)
	{
		const TArray<UNewSettingOption*> SoundOptionArray = SettingOptionContainer->GetSoundSettingOptionArray();
		if (SoundOptionArray.Num() > 0)
		{
			for (UNewSettingOption* SoundOption : SoundOptionArray)
			{
				SoundOption->SetVisibility(ESlateVisibility::Visible);
			}
		}
	}
}

void UNewSettingSubUI::HideSettingOption(UNewSettingMenu* SettingMenu) const
{
	const UNewSettingMenu* GraphicMenu = SettingMenuContainer->GetGraphicSettingButton();
	if (SettingMenu == GraphicMenu)
	{
		const TArray<UNewSettingOption*> GraphicOptionArray = SettingOptionContainer->GetGraphicSettingOptionArray();
		if (GraphicOptionArray.Num() > 0)
		{
			for (UNewSettingOption* GraphicOption : GraphicOptionArray)
			{
				GraphicOption->SetVisibility(ESlateVisibility::Collapsed);
			}
		}
	}

	const UNewSettingMenu* SoundMenu = SettingMenuContainer->GetSoundSettingButton();
	if (SettingMenu == SoundMenu)
	{
		const TArray<UNewSettingOption*> SoundOptionArray = SettingOptionContainer->GetSoundSettingOptionArray();
		if (SoundOptionArray.Num() > 0)
		{
			for (UNewSettingOption* SoundOption : SoundOptionArray)
			{
				SoundOption->SetVisibility(ESlateVisibility::Collapsed);
			}
		}
	}
}
