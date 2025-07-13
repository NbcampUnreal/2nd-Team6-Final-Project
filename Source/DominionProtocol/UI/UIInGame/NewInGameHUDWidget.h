// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseHUDWidget.h"
#include "NewInGameHUDWidget.generated.h"

class AInGameController;


UCLASS()
class DOMINIONPROTOCOL_API UNewInGameHUDWidget : public UBaseHUDWidget
{
	GENERATED_BODY()


public:
	UFUNCTION()
	void ActivateAlertUI();

	UFUNCTION()
	void DeactivateAlertUI();
	
	UFUNCTION()
	void ActivateCrackMenuUI();

	UFUNCTION()
	void DeactivateCrackMenuUI();

	UFUNCTION()
	void ActivateMainMenuUI();
	
	UFUNCTION()
	void DeactivateMainMenuUI();

	UFUNCTION()
	void ActivateDialogueUI();

	UFUNCTION()
	void DeactivateDialogueUI();

	// UFUNCTION()
	// void ShowAllDisplay();
	//
	// UFUNCTION()
	// void HideAllDisplay();

protected:
	virtual void NativeConstruct() override;

protected:

#pragma region HUD
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UUserWidget> StatusBarDisplay;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UUserWidget> ItemSlotsDisplay;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UUserWidget> InteractionDisplay;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UUserWidget> EventBoxDisplay;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UUserWidget> BossMonsterHPBarDisplay;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UUserWidget> LockOnDisplay;

#pragma endregion

#pragma region UI
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UUserWidget> AlertUI;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UUserWidget> CrackMenuUI;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UUserWidget> MainMenuUI;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UUserWidget> DialogueUI;

#pragma endregion
};
