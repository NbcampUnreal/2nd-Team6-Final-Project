// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseContentContainer.h"
#include "NewSettingMenuContainer.generated.h"

class UNewSettingMenu;

UCLASS()
class DOMINIONPROTOCOL_API UNewSettingMenuContainer : public UBaseContentContainer
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UNewSettingMenu> GraphicSettingButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UNewSettingMenu> SoundSettingButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UNewSettingMenu> ExitButton;
};
