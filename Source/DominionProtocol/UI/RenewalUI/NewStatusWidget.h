// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NewStatusWidget.generated.h"


UCLASS()
class DOMINIONPROTOCOL_API UNewStatusWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class UStatusComponent> StatusComponent;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class UDomiGameInstance> DomiGameInstance;
};
