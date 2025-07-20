// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseHUDWidget.h"
#include "NewTitleHUDWidget.generated.h"

UCLASS()
class DOMINIONPROTOCOL_API UNewTitleHUDWidget : public UBaseHUDWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	
	// for Button Event
	UFUNCTION()
	void ActivateSaveSlotUI();

	UFUNCTION()
	void DeactivateSaveSlotUI();

	UFUNCTION()
	void ExitGame() const;

	UFUNCTION()
	void BindButtonActionDelegates();

	UFUNCTION()
	void BindInputActionDelegates();

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UUserWidget> TitleMenuUI;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UUserWidget> SaveSlotContainerUI;

};
