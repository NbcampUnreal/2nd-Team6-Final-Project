// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NewShotcutButton.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnShotcutButtonClickedEvent);

class UTextBlock;
class USizeBox;

UCLASS()
class DOMINIONPROTOCOL_API UNewShotcutButton : public UUserWidget
{
	GENERATED_BODY()

public:
	FOnShotcutButtonClickedEvent OnShotcutButtonClickedEvent;

	UFUNCTION(BlueprintCallable)
	void BroadcastButtonClickedEvent() const;
	
	UFUNCTION(BlueprintCallable)
	void SetShotcutKeyText(const FText& NewShotcutKeyText);

	UFUNCTION(BlueprintCallable)
	void SetShotcutScriptText(const FText& NewShotcutScriptText);

protected:
	UFUNCTION()
	void SetInfo();

	UFUNCTION()
	void DisplayInfo();

	virtual void NativePreConstruct() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Size = {40, 40};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ShotcutKeyText = FText::FromString(TEXT("Q"));
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ShotcutScriptText = FText::FromString(TEXT("돌아가기"));
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> ShotcutKey;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> ShotcutScript;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<USizeBox> Sizer;
};
