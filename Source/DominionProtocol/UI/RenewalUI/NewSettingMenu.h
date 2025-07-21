// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseContent.h"
#include "NewSettingMenu.generated.h"

class UTextBlock;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnGetFocusSettingMenuEvent, class UNewSettingMenu*)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnLoseFocusSettingMenuEvent, class UNewSettingMenu*)

UCLASS()
class DOMINIONPROTOCOL_API UNewSettingMenu : public UBaseContent
{
	GENERATED_BODY()

public:
	FOnGetFocusSettingMenuEvent OnGetFocusSettingMenuEvent;
	FOnLoseFocusSettingMenuEvent OnLoseFocusSettingMenuEvent;
	
	virtual void SetInfo() override;

	virtual void GetFocus() override;

	virtual void LoseFocus() override;

protected:
	UFUNCTION(BLueprintImplementableEvent)
	void GetFocusEffects();

	UFUNCTION(BlueprintImplementableEvent)
	void LoseFocusEffects();
	
	virtual void NativePreConstruct() override;

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> SettingButtonName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText SettingMenuNameText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText SettingMenuDescription;
};
