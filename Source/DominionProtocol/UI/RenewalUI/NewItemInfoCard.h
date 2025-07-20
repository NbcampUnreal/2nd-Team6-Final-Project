// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Blueprint/UserWidget.h"
#include "NewItemInfoCard.generated.h"

enum class EItemType : uint8;
class UImage;
class UTextBlock;

UCLASS()
class DOMINIONPROTOCOL_API UNewItemInfoCard : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetInfo(const FGameplayTag ItemTag, const int32 ItemQuantity);

	UFUNCTION(BlueprintImplementableEvent)
	void SetItemEffectsInfo(const FGameplayTag ItemTag, const EItemType ItemType);
	
protected:
	virtual void NativeConstruct() override;	

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UDataTable> ItemDataTable;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UImage> ItemImage;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemName;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemAmount;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemExplain;

	
};
