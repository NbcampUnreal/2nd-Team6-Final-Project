// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Util/GameTagList.h"
#include "NewEventBoxDisplay.generated.h"

class UVerticalBox;

UCLASS()
class DOMINIONPROTOCOL_API UNewEventBoxDisplay : public UUserWidget
{
	GENERATED_BODY()


public:
	UFUNCTION()
	void OnUpdateEventGetEssence(const int32 NewEssence);
	UFUNCTION()
	void OnUpdateEventAddItem(const FGameplayTag AddItemTag, const int32 Quantity);
	UFUNCTION()
	void OnUpdateEventUseItem(const FGameplayTag UseItemTag);

	// 블루프린트에서 텍스트 가공 후 위젯에 추가 예정 
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateEventGetEssence(const int32 NewEssence);
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateEventAddItem(const FGameplayTag AddItemTag, const int32 Quantity);
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateEventUseItem(const FGameplayTag UseItemTag);
	
protected:
	virtual void NativeConstruct() override;

	void HandleBindEventDelegates();

	UFUNCTION(BlueprintCallable)
	UUserWidget* GetEventTextWidgetToPool();

	UFUNCTION(BlueprintCallable)
	void ReturnEventTextWidgetToPool(UUserWidget* TextWidget);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UUserWidget> EventTextWidgetClass;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UVerticalBox> EventTextContainer;
	
	UPROPERTY(BlueprintReadWrite)
	TArray<TObjectPtr<UUserWidget>> EventTextPool;

	UPROPERTY(BlueprintReadWrite)
	TArray<TObjectPtr<UUserWidget>> ActiveEventTextArray;

	UPROPERTY(BlueprintReadWrite)
	int32 WidgetPoolMaxCount = 12;
};
