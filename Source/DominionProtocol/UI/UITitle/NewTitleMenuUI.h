// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/UIInterface.h"
#include "UI/BaseContentContainer.h"
#include "NewTitleMenuUI.generated.h"

class UNewTitleMenuButton;

UCLASS()
class DOMINIONPROTOCOL_API UNewTitleMenuUI : public UBaseContentContainer, public IUIInterface
{
	GENERATED_BODY()

public:
	virtual UInputMappingContext* GetInputMappingContext_Implementation() const override;

	UNewTitleMenuButton* GetStartGameButton() const { return StartGameButton; }

	UNewTitleMenuButton* GetExitGameButton() const { return ExitGameButton; }
	
protected:
	UFUNCTION()
	void OnConfirmSelection() const;

	virtual void NativeConstruct() override;

	void BindInputActionDelegates();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputMappingContext> TitleMenuMappingContext;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UNewTitleMenuButton> StartGameButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UNewTitleMenuButton> ExitGameButton;
};
