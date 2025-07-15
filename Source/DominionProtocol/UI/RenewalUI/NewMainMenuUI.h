// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interface/UIInterface.h"
#include "NewMainMenuUI.generated.h"

class UBaseContentContainer;
class UBaseHUDWidget;

UCLASS()
class DOMINIONPROTOCOL_API UNewMainMenuUI : public UUserWidget, public IUIInterface
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual UInputMappingContext* GetInputMappingContext_Implementation() const override;

protected:
	virtual void NativeConstruct() override;

	void BindMainMenuSubUIAndMainMenuButtonContainer() const;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UBaseContentContainer> MainMenuButtonContainer;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UBaseHUDWidget> MainMenuSubUIContainer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputMappingContext> MainMenuUIMappingContext;
};
