// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseHUDWidget.h"
#include "NewTitleHUDWidget.generated.h"

class ATitleController;

UCLASS()
class DOMINIONPROTOCOL_API UNewTitleHUDWidget : public UBaseHUDWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	
	// for Button Event
	UFUNCTION(BlueprintCallable)
	void ActivateSaveSlotUI();

	UFUNCTION(BlueprintCallable)
	void DeactivateSaveSlotUI();

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UUserWidget> TitleMenuUI;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UUserWidget> SaveSlotBoxUI;

};
