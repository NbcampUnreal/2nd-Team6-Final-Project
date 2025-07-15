// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseHUDWidget.h"
#include "WorldObjects/DialogueManager.h"
#include "NewInGameHUDWidget.generated.h"

class AInGameController;


UCLASS()
class DOMINIONPROTOCOL_API UNewInGameHUDWidget : public UBaseHUDWidget
{
	GENERATED_BODY()


public:
	UFUNCTION()
	void ActivateCrackMenuUI();

	UFUNCTION()
	void DeactivateCrackMenuUI();

	UFUNCTION()
	void ActivateMainMenuUI();
	
	UFUNCTION(BlueprintCallable)
	void DeactivateMainMenuUI();

	UFUNCTION()
	void ActivateDialogueUI();

	UFUNCTION()
	void DeactivateDialogueUI();

protected:
	virtual void NativeConstruct() override;
	
	template<typename T>
	void BindDialogueSources();
	
	void BindInputActionDelegates();
	void BindCreateDialogueDelegate();
	void BindActivateDialogueDelegate(UDialogueManager* DialogueManager);
	void BindDialogueTypingFinishedDelegate();

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
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UUserWidget> AlertDisplay;

#pragma endregion

#pragma region UI
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UUserWidget> CrackMenuUI;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UUserWidget> MainMenuUI;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UUserWidget> DialogueUI;

#pragma endregion
};
