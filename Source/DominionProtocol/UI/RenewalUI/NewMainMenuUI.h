// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NewMainMenuUI.generated.h"

class UBaseContentContainer;
class UBaseHUDWidget;

UCLASS()
class DOMINIONPROTOCOL_API UNewMainMenuUI : public UUserWidget
{
	GENERATED_BODY()


protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UBaseContentContainer> MainMenuButtonContainer;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UBaseHUDWidget> MainMenuSubUIContainer;
};
