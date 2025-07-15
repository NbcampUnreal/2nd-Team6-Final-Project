// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseContentContainer.h"
#include "NewItemFilterContainer.generated.h"

UCLASS()
class DOMINIONPROTOCOL_API UNewItemFilterContainer : public UBaseContentContainer
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	void BindInputActionDelegates();
};
