// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseContent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FRequestChangingFocusIndexEvent, int32)

UCLASS(Abstract)
class DOMINIONPROTOCOL_API UBaseContent : public UUserWidget
{
	GENERATED_BODY()

public:
	FRequestChangingFocusIndexEvent RequestChangingFocusIndexEvent;
	
	virtual void SetInfo();
	
	virtual void SetInfoEmpty();

	UFUNCTION(BlueprintCallable)
	virtual void RequestChangingFocusIndex() const;
	
	UFUNCTION()
	virtual void GetFocus();

	UFUNCTION()
	virtual void LoseFocus();

	UFUNCTION()
	void SetContentIndex(const int32 NewFocusIndex) { ContentIndex = NewFocusIndex; }

	UFUNCTION()
	int32 GetContentIndex() const { return ContentIndex; }

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(BlueprintReadWrite)
	int32 ContentIndex = -1;
	
};
