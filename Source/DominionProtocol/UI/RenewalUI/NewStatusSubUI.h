// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NewStatusSubUI.generated.h"


UCLASS()
class DOMINIONPROTOCOL_API UNewStatusSubUI : public UUserWidget
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
