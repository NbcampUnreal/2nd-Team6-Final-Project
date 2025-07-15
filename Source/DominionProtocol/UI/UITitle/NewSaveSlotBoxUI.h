// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/UIInterface.h"
#include "UI/BaseContentContainer.h"
#include "NewSaveSlotBoxUI.generated.h"

class UVerticalBox;
class UNewSaveSlot;
class USaveManagerSubsystem;

UCLASS()
class DOMINIONPROTOCOL_API UNewSaveSlotBoxUI : public UBaseContentContainer, public IUIInterface
{
	GENERATED_BODY()

public:
	virtual UInputMappingContext* GetInputMappingContext_Implementation() const override;
	
	UFUNCTION(BlueprintCallable)
	void RefreshSlotData(const ESlateVisibility VisibilityState);
	
	// For Input Action 
	UFUNCTION(BlueprintImplementableEvent)
	void OnStartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void OnDeleteGame();

	UFUNCTION(BlueprintImplementableEvent)
	void OnBackToTitleMenu();

	UFUNCTION()
	void OnMoveSelectionUp();

	UFUNCTION()
	void OnMoveSelectionDown();

	FORCEINLINE class USaveManagerSubsystem* GetSaveManagerSubsystemInstance() const { return SaveManagerSubsystemInstance; }

protected:
	UFUNCTION(BlueprintCallable)
	void StartGame() const;
	
	UFUNCTION(BlueprintCallable)
	void LoadGame() const;
	
	UFUNCTION(BlueprintCallable)
	void DeleteGame();

	UFUNCTION()
	void InputSaveSlotData(UNewSaveSlot* SaveSlot) const;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void BindInputActionDelegates();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UDataTable> PastCrackImageDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UDataTable> PresentCrackImageDataTable;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<USaveManagerSubsystem> SaveManagerSubsystemInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputMappingContext> TitleSlotUIMappingContext;
};
