// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interface/UIInterface.h"
#include "NewStatusSubUI.generated.h"

class UStatusComponent;
class UDomiGameInstance;
class UInputMappingContext;

UCLASS()
class DOMINIONPROTOCOL_API UNewStatusSubUI : public UUserWidget, public IUIInterface
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateStatusInfoEvent();

	UFUNCTION()
	void RefreshStatusInfo(const ESlateVisibility NewVisibility);

	virtual UInputMappingContext* GetInputMappingContext_Implementation() const override;
	
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UStatusComponent> StatusComponent;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UDomiGameInstance> DomiGameInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputMappingContext> StatusSubUIMappingContext;
};
