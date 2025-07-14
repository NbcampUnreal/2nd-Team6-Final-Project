// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseContent.h"
#include "NewCrackMenuButton.generated.h"

UCLASS()
class DOMINIONPROTOCOL_API UNewCrackMenuButton : public UBaseContent
{
	GENERATED_BODY()

public:
	virtual void SetInfo() override;
	
};
