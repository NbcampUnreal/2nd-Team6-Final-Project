// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseHUDWidget.h"
#include "DomiInGameHUDWidget.generated.h"

class AInGameController;


UCLASS()
class DOMINIONPROTOCOL_API UDomiInGameHUDWidget : public UBaseHUDWidget
{
	GENERATED_BODY()


public:
	UFUNCTION()
	void OnShowCrackMenuWidget();

	UFUNCTION(BlueprintImplementableEvent)
	void ShowCrackMenuWidget();

	// Binding Input Action
	UFUNCTION()
	void OnMainMenuSwitchShowAndHideWidget();

	UFUNCTION(BlueprintImplementableEvent)
	void MainMenuSwitchShowAndHideWidget();

	UFUNCTION()
	void OnDialogueChangedNextStoryState();

	UFUNCTION(BlueprintImplementableEvent)
	void DialogueChangedNextStoryState();

	//
	UFUNCTION(BlueprintCallable)
	void ChangeWidgetZOrder(const UUserWidget* TargetWidget, const int32 NewZOrder);

protected:
	virtual void NativeConstruct() override;

	void BindInputActionDelegates();


protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AInGameController> OwningController;

#pragma region HUD
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UUserWidget> StatusBarWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UUserWidget> ItemSlotsWidget;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UUserWidget> InteractionWidget;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UUserWidget> EventBoxWidget;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UUserWidget> BossMonsterHPBar;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UUserWidget> LockOnHUDWidget;

#pragma endregion

#pragma region UI 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UUserWidget> AlertWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UUserWidget> CrackMenuWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UUserWidget> MainMenuWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UUserWidget> DialogueWidget;

	
#pragma endregion
};
