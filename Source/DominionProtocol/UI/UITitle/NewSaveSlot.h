// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseContent.h"
#include "NewSaveSlot.generated.h"

class UImage;
class UTextBlock;
class USaveManagerSubsystem;

UCLASS()
class DOMINIONPROTOCOL_API UNewSaveSlot : public UBaseContent
{
	GENERATED_BODY()

public:
	virtual void SetInfo() override;
	
	void SetInfo(bool ExistSaveSlotData, UTexture2D* CrackImage, const FString& GameIndexToString, const FString& SaveTimeToString, const
	             FString
	             & PlayTimeToString, const FText& CurrentCrackNameToText, const FText& CurrentLevelToString, const FString&
	             PlayerLevelToString);

	virtual void SetInfoEmpty() override;

	virtual void GetFocus() override;

	UFUNCTION(BlueprintImplementableEvent)
	void GetFocusEffects();

	virtual void LoseFocus() override;

	UFUNCTION(BlueprintImplementableEvent)
	void LoseFocusEffects();

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY()
	TObjectPtr<USaveManagerSubsystem> SaveManagerSubsystemInstance;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> CrackMapImage;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> GameIndex;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> SaveTime;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> PlayTime;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CurrentLevelName;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CurrentCrackName;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> PlayerLevel;

	UPROPERTY(BlueprintReadOnly)
	bool bExistSaveSlotData = false;
};
