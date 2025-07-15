// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnumAndStruct/EDisplaySubMenuUI.h"
#include "UI/BaseContent.h"
#include "NewMenuSelecter.generated.h"

class USizeBox;
class UTextBlock;
class UBorder;
class UNewMainMenuUI;

UCLASS()
class DOMINIONPROTOCOL_API UNewMenuSelecter : public UBaseContent
{
	GENERATED_BODY()

public:
	virtual void SetInfo() override;

	virtual void GetFocus() override;

	UFUNCTION(BlueprintImplementableEvent)
	void GetFocusEffects();

	virtual void LoseFocus() override;

	UFUNCTION(BlueprintImplementableEvent)
	void LoseFocusEffects();

protected:
	virtual void NativeConstruct() override;

	virtual void NativePreConstruct() override;

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<USizeBox> Sizer;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> MenuSelecterName;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> SelecterName;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UBorder> SelectEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText SelecterNameText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Size = {200.f,50.f};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDisplaySubMenuUI DisplayMenu = EDisplaySubMenuUI::Default;
};
