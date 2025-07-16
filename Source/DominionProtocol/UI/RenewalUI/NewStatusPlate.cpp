// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RenewalUI/NewStatusPlate.h"

#include "NewShotcutButton.h"
#include "Components/Border.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"

void UNewStatusPlate::SetInfo(const FText NewStatusValue1, const FText NewStatusValue2, const FText NewStatusValue3, const FText NewStatusValue4, const FText NewStatusValue5)
{
	StatusValue1->SetText(NewStatusValue1);
	StatusValue2->SetText(NewStatusValue2);
	StatusValue3->SetText(NewStatusValue3);
	StatusValue4->SetText(NewStatusValue4);
	StatusValue5->SetText(NewStatusValue5);

	for (int32 i = 0; i < StatusButtonArray.Num(); ++i)
	{
		StatusButtonArray[i]->SetShotcutKeyText(ShotcutKeyTextArray[i]);
		// StatusPlate 에서는 ShotcutScript 를 사용하지 않으므로 비워둔다
		StatusButtonArray[i]->SetShotcutScriptText(FText::FromString(TEXT("")));
	}

	DisplayInfo();
}

void UNewStatusPlate::DisplayInfo()
{
	StatusTitle->SetText(StatusTitleText);
	StatusName1->SetText(StatusNameText1);
	StatusName2->SetText(StatusNameText2);
	StatusName3->SetText(StatusNameText3);
	StatusName4->SetText(StatusNameText4);
	StatusName5->SetText(StatusNameText5);

	for (int32 i = 0; i < StatusNameArray.Num(); ++i)
	{
		if (StatusNameArray[i]->GetText().IsEmpty())
		{
			StatusBorderArray[i]->SetVisibility(ESlateVisibility::Collapsed);
		}
		else
		{
			StatusBorderArray[i]->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void UNewStatusPlate::SetInfoTextColor(const FSlateColor NewTextColor1, const FSlateColor NewTextColor2, const FSlateColor NewTextColor3, const FSlateColor NewTextColor4, const FSlateColor NewTextColor5) const
{
	StatusValue1->SetColorAndOpacity(NewTextColor1);
	StatusValue2->SetColorAndOpacity(NewTextColor2);
	StatusValue3->SetColorAndOpacity(NewTextColor3);
	StatusValue4->SetColorAndOpacity(NewTextColor4);
	StatusValue5->SetColorAndOpacity(NewTextColor5);
}

void UNewStatusPlate::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	StatusBorderArray.AddUnique(StatusBorder1);
	StatusBorderArray.AddUnique(StatusBorder2);
	StatusBorderArray.AddUnique(StatusBorder3);
	StatusBorderArray.AddUnique(StatusBorder4);
	StatusBorderArray.AddUnique(StatusBorder5);
	
	StatusInfoContainerArray.AddUnique(StatusInfoContainer1);
	StatusInfoContainerArray.AddUnique(StatusInfoContainer2);
	StatusInfoContainerArray.AddUnique(StatusInfoContainer3);
	StatusInfoContainerArray.AddUnique(StatusInfoContainer4);
	StatusInfoContainerArray.AddUnique(StatusInfoContainer5);

	for (UHorizontalBox* StatusInfoContainer : StatusInfoContainerArray)
	{
		TArray<UWidget*> StatusInfoWidgetArray = StatusInfoContainer->GetAllChildren();
		if (StatusInfoWidgetArray.Num() > 0)
		{
			for (UWidget* StatusInfoWidget : StatusInfoWidgetArray)
			{
				const FString WidgetName = StatusInfoWidget->GetName();
				if (WidgetName.Contains(TEXT("Name")))
				{
					auto* StatusNameWidget = Cast<UTextBlock>(StatusInfoWidget);
					StatusNameArray.AddUnique(StatusNameWidget);
				}
				else if (WidgetName.Contains(TEXT("Value")))
				{
					auto* StatusValueWidget = Cast<UTextBlock>(StatusInfoWidget);
					StatusValueArray.AddUnique(StatusValueWidget);
				}
				else if (WidgetName.Contains(TEXT("Button")))
				{
					auto* StatusButtonWidget = Cast<UNewShotcutButton>(StatusInfoWidget);
					StatusButtonArray.AddUnique(StatusButtonWidget);
				}
			}
		}
	}

	// TextArray 는 AddUnique 사용이 안된다. 왜냐하면 FText 는 = 오퍼레이터를 사용할 수 없지만 AddUnique 는 = 연산자를 사용하여 비교하기 때문 
	ShotcutKeyTextArray.Add(ShotcutKey1_1);
	ShotcutKeyTextArray.Add(ShotcutKey1_2);
	ShotcutKeyTextArray.Add(ShotcutKey2_1);
	ShotcutKeyTextArray.Add(ShotcutKey2_2);
	ShotcutKeyTextArray.Add(ShotcutKey3_1);
	ShotcutKeyTextArray.Add(ShotcutKey3_2);
	ShotcutKeyTextArray.Add(ShotcutKey4_1);
	ShotcutKeyTextArray.Add(ShotcutKey4_2);
	ShotcutKeyTextArray.Add(ShotcutKey5_1);
	ShotcutKeyTextArray.Add(ShotcutKey5_2);

	SetInfo();
}