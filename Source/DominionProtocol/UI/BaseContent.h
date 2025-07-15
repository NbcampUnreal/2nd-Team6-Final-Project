// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseContent.generated.h"


UCLASS(Abstract)
class DOMINIONPROTOCOL_API UBaseContent : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void SetInfo();

	UFUNCTION()
	virtual void SetInfoEmpty();

	UFUNCTION()
	virtual void GetFocus();

	UFUNCTION()
	virtual void LoseFocus();

	UFUNCTION()
	void SetContentIndex(const int32 NewFocusIndex) { ContentIndex = NewFocusIndex; }

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(BlueprintReadWrite)
	int32 ContentIndex = -1;
	
};
