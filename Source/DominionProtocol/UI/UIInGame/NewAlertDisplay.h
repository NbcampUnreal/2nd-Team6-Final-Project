// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NewAlertDisplay.generated.h"

class UTextBlock;

UCLASS()
class DOMINIONPROTOCOL_API UNewAlertDisplay : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void OnShowPlayerDeathAlert();

	UFUNCTION()
	void OnShowBossKillAlert(AActor* DeadMonster);

	UFUNCTION()
	void OnShowEssenceRestoredAlert(const int32 NewEssenceAmount);

	UFUNCTION()
	void OnShowCrackActivationAlert(const FText CrackName);
	
protected:
	UFUNCTION()
	void StartAlertDisplayDeactivateTimer();
	
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

	FTimerHandle AlertDisplayDeactivateTimer;
	
};
