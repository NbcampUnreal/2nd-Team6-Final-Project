// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RenewalUI/NewMainMenuUI.h"

#include "Components/CanvasPanelSlot.h"
#include "Player/InGameController.h"

void UNewMainMenuUI::NativeConstruct()
{
	Super::NativeConstruct();

	BindInputActionDelegates();
}

void UNewMainMenuUI::BindInputActionDelegates()
{
	auto* InGameController = Cast<AInGameController>(GetOwningPlayer());
	if (InGameController)
	{
		InGameController->OnMainMenuUIDeactivateActionEvent.AddUObject(this, &UNewMainMenuUI::OnPressButtonQ);
	}
}

void UNewMainMenuUI::ChangeWidgetZOrder(const UUserWidget* TargetWidget, const int32 NewZOrder)
{
	if (!IsValid(TargetWidget))
	{
		return;
	}

	UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(TargetWidget->Slot);

	if (IsValid(CanvasSlot))
	{
		CanvasSlot->SetZOrder(NewZOrder);
	}
}

void UNewMainMenuUI::OnPressButtonZ()
{
	PressButtonZ();
}

void UNewMainMenuUI::OnPressButtonC()
{
	PressButtonC();
}

void UNewMainMenuUI::OnPressButtonA()
{
	PressButtonA();
}

void UNewMainMenuUI::OnPressButtonD()
{
	PressButtonD();
}

void UNewMainMenuUI::OnPressButtonE()
{
	PressButtonE();
}

void UNewMainMenuUI::OnPressButtonR()
{
	PressButtonR();
}

void UNewMainMenuUI::OnPressButtonSpaceBar()
{
	PressButtonSpaceBar();
}

void UNewMainMenuUI::OnPressButtonQ()
{
	PressButtonQ();
}
