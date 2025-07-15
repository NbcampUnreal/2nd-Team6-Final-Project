// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/UIInterface.h"
#include "UI/BaseContentContainer.h"
#include "NewCrackMenuUI.generated.h"

class UVerticalBox;

UENUM(BlueprintType)
enum class ECurrentDisplayOption : uint8
{
	CrackTeleport			UMETA(DisplayName="CrackTeleport"),
	AbilityEnforce			UMETA(DisplayName="AbilityEnforce"),
	PotionEnforce			UMETA(DisplayName="PotionEnforce"),
	Default					UMETA(DisplayName="Default")
};

UCLASS()
class DOMINIONPROTOCOL_API UNewCrackMenuUI : public UBaseContentContainer, public IUIInterface
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual UInputMappingContext* GetInputMappingContext_Implementation() const override;

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void BindInputActionDelegates();

protected:
	UPROPERTY(BlueprintReadWrite)
	ECurrentDisplayOption CurrentDisplayOption = ECurrentDisplayOption::Default;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputMappingContext> CrackMenuUIMappingContext;
};
