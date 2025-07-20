// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseContent.h"
#include "NewTitleMenuButton.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnTitleMenuButtonClickedEvent)

class UTextBlock;
class USizeBox;

UCLASS()
class DOMINIONPROTOCOL_API UNewTitleMenuButton : public UBaseContent
{
	GENERATED_BODY()

public:
	FOnTitleMenuButtonClickedEvent OnTitleMenuButtonClickedEvent;
	
	virtual void SetInfo() override;

	virtual void GetFocus() override;

	virtual void LoseFocus() override;

	UFUNCTION(BlueprintCallable)
	void BroadcastButtonClickEvent() const;

protected:
	virtual void NativePreConstruct() override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void GetFocusEffect();
	
	UFUNCTION(BlueprintImplementableEvent)
	void LoseFocusEffect();

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> ButtonName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ButtonNameText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<USizeBox> Sizer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Size = {320.f,80.f};
};
