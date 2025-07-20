// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/UIInterface.h"
#include "UI/BaseContentContainer.h"
#include "NewSaveSlotContainerUI.generated.h"

class UVerticalBox;
class UNewSaveSlot;
class USaveManagerSubsystem;
class UNewShotcutButton;

UCLASS()
class DOMINIONPROTOCOL_API UNewSaveSlotContainerUI : public UBaseContentContainer, public IUIInterface
{
	GENERATED_BODY()

public:
	virtual UInputMappingContext* GetInputMappingContext_Implementation() const override;
	
	UFUNCTION(BlueprintCallable)
	void RefreshSlotData(const ESlateVisibility VisibilityState);
	
	// For Input Action 
	UFUNCTION()
	void OnStartGame();

	UFUNCTION()
	void OnDeleteGame();

	FORCEINLINE USaveManagerSubsystem* GetSaveManagerSubsystemInstance() const { return SaveManagerSubsystemInstance; }

	// Getter
	UNewShotcutButton* GetStartButton() const { return StartButton; }
	UNewShotcutButton* GetDeleteButton() const { return DeleteButton; }
	UNewShotcutButton* GetBackButton() const { return BackButton; }

protected:
	UFUNCTION(BlueprintCallable)
	void StartGame() const;
	
	UFUNCTION(BlueprintCallable)
	void LoadGame() const;
	
	UFUNCTION(BlueprintCallable)
	void DeleteGame();

	UFUNCTION()
	void SetSaveSlotData(UNewSaveSlot* SaveSlot) const;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void BindInputActionDelegates();

	UFUNCTION()
	void BindButtonActionDelegates();
	
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UNewShotcutButton> StartButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UNewShotcutButton> DeleteButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UNewShotcutButton> BackButton;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UDataTable> PastCrackImageDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UDataTable> PresentCrackImageDataTable;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<USaveManagerSubsystem> SaveManagerSubsystemInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputMappingContext> TitleSlotUIMappingContext;
};
