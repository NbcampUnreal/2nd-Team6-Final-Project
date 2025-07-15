// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NewStatusPlate.generated.h"

class UTextBlock;
class UBorder;
class UHorizontalBox;
class UNewShotcutButton;

UCLASS()
class DOMINIONPROTOCOL_API UNewStatusPlate : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetInfo(const FText NewStatusValue1 = FText::GetEmpty(), const FText NewStatusValue2 = FText::GetEmpty(), const FText NewStatusValue3 = FText::GetEmpty(), const FText NewStatusValue4 = FText::GetEmpty(), const FText
	              NewStatusValue5 = FText::GetEmpty());

protected:
	void DisplayInfo();

	UFUNCTION(BlueprintCallable)
	void SetInfoTextColor(const FSlateColor NewTextColor1, const FSlateColor NewTextColor2, const FSlateColor NewTextColor3, const FSlateColor
	                       NewTextColor4, const FSlateColor NewTextColor5) const;

	virtual void NativePreConstruct() override;



protected:
	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<UTextBlock>> StatusNameArray;

	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<UTextBlock>> StatusValueArray;

	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<UBorder>> StatusBorderArray;

	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<UHorizontalBox>> StatusInfoContainerArray;

	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<UNewShotcutButton>> StatusButtonArray;

	UPROPERTY(BlueprintReadOnly)
	TArray<FText> ShotcutKeyTextArray;

#pragma region Value
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText StatusTitleText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText StatusNameText1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText StatusNameText2;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText StatusNameText3;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText StatusNameText4;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText StatusNameText5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ShotcutKey1_1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ShotcutKey1_2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ShotcutKey2_1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ShotcutKey2_2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ShotcutKey3_1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ShotcutKey3_2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ShotcutKey4_1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ShotcutKey4_2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ShotcutKey5_1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ShotcutKey5_2;

#pragma endregion
	
#pragma region Widgets
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> StatusTitle;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UBorder> StatusBorder1;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> StatusName1;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> StatusValue1;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UBorder> StatusBorder2;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> StatusName2;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> StatusValue2;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UBorder> StatusBorder3;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> StatusName3;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> StatusValue3;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UBorder> StatusBorder4;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> StatusName4;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> StatusValue4;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UBorder> StatusBorder5;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> StatusName5;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> StatusValue5;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UHorizontalBox> StatusInfoContainer1;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UHorizontalBox> StatusInfoContainer2;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UHorizontalBox> StatusInfoContainer3;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UHorizontalBox> StatusInfoContainer4;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UHorizontalBox> StatusInfoContainer5;

#pragma endregion
};
