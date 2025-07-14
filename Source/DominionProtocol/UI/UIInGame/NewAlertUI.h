// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NewAlertUI.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAlertDisplayFinishedEvent)

class UTextBlock;

UCLASS()
class DOMINIONPROTOCOL_API UNewAlertUI : public UUserWidget
{
	GENERATED_BODY()

public:
	FOnAlertDisplayFinishedEvent OnAlertDisplayFinishedEvent;
	
	UFUNCTION()
	void OnShowPlayerDeathAlert() const;

	UFUNCTION()
	void OnShowBossKillAlert(AActor* DeadMonster) const;

	UFUNCTION()
	void OnShowEssenceRestoredAlert(const int32 NewEssenceAmount) const;

	UFUNCTION()
	void OnShowCrackActivationAlert(const FText CrackName) const;
	
protected:
	UFUNCTION()
	void StartAlertUIDeactivateTimer();

	UFUNCTION()
	void DeactivateAlertUIEvent() const;
	
	virtual void NativeConstruct() override;

	UFUNCTION()
	void BindAlertDelegates();

	UFUNCTION()
	void BindRestoredEssence(class ADropEssence* DropEssence);

public:
	FDelegateHandle HandleBindRestoredEssence;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> AlertText;

	FTimerHandle AlertUIDeactivateTimer;
	
};
