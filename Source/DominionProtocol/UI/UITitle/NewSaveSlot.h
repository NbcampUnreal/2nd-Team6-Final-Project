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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UDataTable> PastCrackImageDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UDataTable> PresentCrackImageDataTable;

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
	bool ExistSaveSlotData = false;
	
};
