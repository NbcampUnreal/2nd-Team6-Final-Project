// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnumAndStruct/EDisplaySubMenuUI.h"
#include "UI/BaseContentContainer.h"
#include "NewMainMenuButtonContainer.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnCurrentDisplaySubMenuUIChangedEvent, EDisplaySubMenuUI);

UCLASS()
class DOMINIONPROTOCOL_API UNewMainMenuButtonContainer : public UBaseContentContainer
{
	GENERATED_BODY()

public:
	FOnCurrentDisplaySubMenuUIChangedEvent OnCurrentDisplaySubMenuUIChangedEvent;

	UFUNCTION(BlueprintCallable)
	void ChangeCurrentDisplaySubUI(const EDisplaySubMenuUI NewDisplaySubMenuUI);

protected:
	UPROPERTY()
	EDisplaySubMenuUI CurrentDisplaySubMenuUI = EDisplaySubMenuUI::Default;
	
};
