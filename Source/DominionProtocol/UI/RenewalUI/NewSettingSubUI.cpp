// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RenewalUI/NewSettingSubUI.h"

#include "DomiFramework/GameInstance/SoundInstanceSubsystem.h"


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

