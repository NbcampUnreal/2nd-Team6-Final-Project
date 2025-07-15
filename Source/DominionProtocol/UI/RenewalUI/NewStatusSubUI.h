// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NewStatusSubUI.generated.h"

class UStatusComponent;
class UDomiGameInstance;
class UInputMappingContext;
class UNewStatusPlate;

UCLASS()
class DOMINIONPROTOCOL_API UNewStatusSubUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION()
	void SetInfo() const;

	UFUNCTION()
	void RefreshStatusInfo(const ESlateVisibility NewVisibility);
	
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UStatusComponent> StatusComponent;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UDomiGameInstance> DomiGameInstance;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UNewStatusPlate> BaseStatus;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UNewStatusPlate> Level;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UNewStatusPlate> AttackStatus;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UNewStatusPlate> BaseAbility;
};
