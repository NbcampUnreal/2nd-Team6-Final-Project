// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseContentContainer.h"
#include "NewMainMenuButtonContainer.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnCurrentDisplaySubMenuUIChangedEvent, int32);

UCLASS()
class DOMINIONPROTOCOL_API UNewMainMenuButtonContainer : public UBaseContentContainer
{
	GENERATED_BODY()

public:
	FOnCurrentDisplaySubMenuUIChangedEvent OnCurrentDisplaySubMenuUIChangedEvent;

protected:
	virtual void NativeConstruct() override;

	virtual void ChangeFocusIndex(const int32 NewFocusIndex) override;
	
	UFUNCTION()
	void ChangeCurrentDisplaySubUI() const;

	UFUNCTION()
	void BindInputActionDelegates();
};
