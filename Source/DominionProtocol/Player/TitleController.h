// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePlayerController.h"
#include "TitleController.generated.h"

#pragma region ForwardDeclaration

DECLARE_MULTICAST_DELEGATE(FOnSlotUIStartGameEvent)
DECLARE_MULTICAST_DELEGATE(FOnSlotUIDeleteGameEvent)
DECLARE_MULTICAST_DELEGATE(FOnSlotUIBackToTitleMenuEvent)
DECLARE_MULTICAST_DELEGATE(FOnSlotUIMoveSelectionUpEvent)
DECLARE_MULTICAST_DELEGATE(FOnSlotUIMoveSelectionDownEvent)
DECLARE_MULTICAST_DELEGATE(FOnMenuUIMoveSelectionUpEvent)
DECLARE_MULTICAST_DELEGATE(FOnMenuUIMoveSelectionDownEvent)
DECLARE_MULTICAST_DELEGATE(FOnMenuUIConfirmSelectionEvent)

#pragma endregion

class UNewTitleHUDWidget;

UCLASS()
class DOMINIONPROTOCOL_API ATitleController : public ABasePlayerController
{
	GENERATED_BODY()

public:
	// Slot UI
	FOnSlotUIStartGameEvent OnSlotUIStartGameEvent;
	FOnSlotUIDeleteGameEvent OnSlotUIDeleteGameEvent;
	FOnSlotUIBackToTitleMenuEvent OnSlotUIBackToTitleMenuEvent;
	FOnSlotUIMoveSelectionUpEvent OnSlotUIMoveSelectionUpEvent;
	FOnSlotUIMoveSelectionDownEvent OnSlotUIMoveSelectionDownEvent;

	// MenuUI
	FOnMenuUIMoveSelectionUpEvent OnMenuUIMoveSelectionUpEvent;
	FOnMenuUIMoveSelectionDownEvent OnMenuUIMoveSelectionDownEvent;
	FOnMenuUIConfirmSelectionEvent OnMenuUIConfirmSelectionEvent;
	
	ATitleController();
	
	void SetupMappingContext(const UInputMappingContext* NewInputMappingContext);

	FORCEINLINE float GetFadeDuration() const { return FadeDuration; }
	
protected:
	UFUNCTION()
	virtual void CreateAndAddHUDWidget() override;
	
	UFUNCTION()
	virtual void SetupMappingContext() override;
	
	UFUNCTION()
	virtual void SetupInputMode() override;

	UFUNCTION()
	virtual void BindInputActions() override;
	
	virtual void BeginPlay() override;
	
#pragma region BindAction
	
	UFUNCTION()
	void OnTitleSlotUIStartGame() const;

	UFUNCTION()
	void OnTitleSlotUIDeleteGame() const;

	UFUNCTION()
	void OnTitleSlotUIBackToTitleMenu() const;

	UFUNCTION()
	void OnTitleSlotUIMoveSelectionUp() const;

	UFUNCTION()
	void OnTitleSlotUIMoveSelectionDown() const;

	UFUNCTION()
	void OnTitleMenuUIMoveSelectionUp() const;

	UFUNCTION()
	void OnTitleMenuUIMoveSelectionDown() const;

	UFUNCTION()
	void OnTitleMenuUIConfirmSelection() const;

#pragma endregion
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UNewTitleHUDWidget> TitleHUDWidgetClass;

	UPROPERTY()
	TObjectPtr<UNewTitleHUDWidget> TitleHUDWidgetInstance;
	
#pragma region MenuUIInputActionsSection

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> InputTitleMenuUIMoveSelectionUp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> InputTitleMenuUIMoveSelectionDown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> InputTitleMenuUIConfirmSelection;


#pragma endregion

#pragma region SlotUIInputActionsSection
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> InputTitleSlotUIStartGame;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> InputTitleSlotUIDeleteGame;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> InputTitleSlotUIBackToTitleMenu;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> InputTitleSlotUIMoveSelectionUp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> InputTitleSlotUIMoveSelectionDown;
	
#pragma endregion
};
