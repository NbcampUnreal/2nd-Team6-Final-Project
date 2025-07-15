// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UITitle/NewSaveSlot.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "DomiFramework/GameInstance/SaveManagerSubsystem.h"

void UNewSaveSlot::SetInfo()
{
	Super::SetInfo();
}

void UNewSaveSlot::SetInfo(const bool ExistSaveSlotData, UTexture2D* CrackImage, const FString& GameIndexToString, const FString& SaveTimeToString, const FString& PlayTimeToString, const FText& CurrentCrackNameToText, const FText& CurrentLevelToString, const FString& PlayerLevelToString)
{
	bExistSaveSlotData = ExistSaveSlotData;
	CrackMapImage->SetBrushFromTexture(CrackImage);
	GameIndex->SetText(FText::FromString(GameIndexToString));
	SaveTime->SetText(FText::FromString(SaveTimeToString));
	PlayTime->SetText(FText::FromString(PlayTimeToString));
	CurrentCrackName->SetText(CurrentCrackNameToText);
	CurrentLevelName->SetText(CurrentLevelToString);
	PlayerLevel->SetText(FText::FromString(PlayerLevelToString));
}

void UNewSaveSlot::SetInfoEmpty()
{
	bExistSaveSlotData = false;
	CrackMapImage->SetBrushFromTexture(nullptr);
	GameIndex->SetText(FText::FromString(TEXT("데이터없음")));
	SaveTime->SetText(FText::FromString(TEXT("-- / -- / --")));
	PlayTime->SetText(FText::FromString(TEXT("총 플레이 시간 -- : --")));
	CurrentLevelName->SetText(FText::FromString(TEXT("-")));
	CurrentCrackName->SetText(FText::FromString(TEXT("-")));
	PlayerLevel->SetText(FText::FromString(TEXT("")));
}

void UNewSaveSlot::GetFocus()
{
	Super::GetFocus();

	GetFocusEffects();
}

void UNewSaveSlot::LoseFocus()
{
	Super::LoseFocus();

	LoseFocusEffects();
}

void UNewSaveSlot::NativeConstruct()
{
	const auto* GameInstance = GetWorld()->GetGameInstance();
	auto* SaveManagerSubsystem = GameInstance->GetSubsystem<USaveManagerSubsystem>();
	
	ensureMsgf(SaveManagerSubsystem, TEXT("Casting failed to SaveManagerSubsystem in UNewSettingWidget"));
	
	if (SaveManagerSubsystem)
	{
		SaveManagerSubsystemInstance = SaveManagerSubsystem;
	}

	// SetInfo 가 포함 된 Super 함수는 마지막에 위치
	Super::NativeConstruct();
}
