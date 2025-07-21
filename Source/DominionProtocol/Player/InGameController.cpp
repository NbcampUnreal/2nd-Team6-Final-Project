// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Util/DevCheatManager.h"
#include "UI/UIInGame/NewInGameHUDWidget.h"
#include "Util/DebugHelper.h"

AInGameController::AInGameController()
{
	static ConstructorHelpers::FClassFinder<UNewInGameHUDWidget> InGameHUDWidgetRef (TEXT("/Game/Blueprints/UI/WBP_DomiInGameHUDWidget.WBP_DomiInGameHUDWidget_C"));
	if (InGameHUDWidgetRef.Class)
	{
		InGameHUDWidgetClass = InGameHUDWidgetRef.Class;	
	}
	
	CheatClass = UDevCheatManager::StaticClass();
}

void AInGameController::BeginPlay()
{
	Super::BeginPlay();
	
	FadeIn();
}

void AInGameController::CreateAndAddHUDWidget()
{
	Super::CreateAndAddHUDWidget();
	
	InGameHUDWidgetInstance = CreateWidget<UNewInGameHUDWidget>(this, InGameHUDWidgetClass);

	if (InGameHUDWidgetInstance)
	{
		InGameHUDWidgetInstance->AddToViewport();
	}
}

void AInGameController::SetupInputMode()
{
	Super::SetupInputMode();

	const FInputModeGameAndUI CurrentInputMode;
	SetInputMode(CurrentInputMode);
	bShowMouseCursor = false;
}

void AInGameController::SetupMappingContext()
{
	Super::SetupMappingContext();

	if (LocalPlayerInputSubsystem)
	{
		RemoveAllMappingContext();
		if (DefaultMappingContext)
		{
			LocalPlayerInputSubsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AInGameController::BindInputActions()
{
	Super::BindInputActions();

	auto* EnhancedInputComp = Cast<UEnhancedInputComponent>(InputComponent);
	check(EnhancedInputComp);

	HelperBindInputAction(EnhancedInputComp, InputMainMenuUIActivateAction, ETriggerEvent::Started, GET_FUNCTION_NAME_CHECKED(AInGameController, OnMainMenuUIActivateAction));
	HelperBindInputAction(EnhancedInputComp, InputMainMenuUIDeactivateAction, ETriggerEvent::Started, GET_FUNCTION_NAME_CHECKED(AInGameController, OnMainMenuUIDeactivateAction));
	HelperBindInputAction(EnhancedInputComp, InputMainMenuUIMoveSelectionLeft, ETriggerEvent::Started, GET_FUNCTION_NAME_CHECKED(AInGameController, OnMainMenuUIMoveSelectionLeft));
	HelperBindInputAction(EnhancedInputComp, InputMainMenuUIMoveSelectionRight, ETriggerEvent::Started, GET_FUNCTION_NAME_CHECKED(AInGameController, OnMainMenuUIMoveSelectionRight));
	HelperBindInputAction(EnhancedInputComp, InputEquipmentUIMoveSelectionUp, ETriggerEvent::Started, GET_FUNCTION_NAME_CHECKED(AInGameController, OnEquipmentUIMoveSelectionUp));
	HelperBindInputAction(EnhancedInputComp, InputEquipmentUIMoveSelectionDown, ETriggerEvent::Started, GET_FUNCTION_NAME_CHECKED(AInGameController, OnEquipmentUIMoveSelectionDown));
	HelperBindInputAction(EnhancedInputComp, InputEquipmentUIEquipItemAction, ETriggerEvent::Started, GET_FUNCTION_NAME_CHECKED(AInGameController, OnEquipmentUIEquipItemAction));
	HelperBindInputAction(EnhancedInputComp, InputEquipmentUIUnequipItemAction, ETriggerEvent::Started, GET_FUNCTION_NAME_CHECKED(AInGameController, OnEquipmentUIUnequipItemAction));
	HelperBindInputAction(EnhancedInputComp, InputItemUIMoveSelectionUp, ETriggerEvent::Started, GET_FUNCTION_NAME_CHECKED(AInGameController, OnItemUIMoveSelectionUp));
	HelperBindInputAction(EnhancedInputComp, InputItemUIMoveSelectionDown, ETriggerEvent::Started, GET_FUNCTION_NAME_CHECKED(AInGameController, OnItemUIMoveSelectionDown));
	HelperBindInputAction(EnhancedInputComp, InputItemUIMoveSelectionLeft, ETriggerEvent::Started, GET_FUNCTION_NAME_CHECKED(AInGameController, OnItemUIMoveSelectionLeft));
	HelperBindInputAction(EnhancedInputComp, InputItemUIMoveSelectionRight, ETriggerEvent::Started, GET_FUNCTION_NAME_CHECKED(AInGameController, OnItemUIMoveSelectionRight));
	HelperBindInputAction(EnhancedInputComp, InputItemUIConsumeItemAction, ETriggerEvent::Started, GET_FUNCTION_NAME_CHECKED(AInGameController, OnItemUIConsumeItemAction));
	HelperBindInputAction(EnhancedInputComp, InputItemUIEquipItemAction, ETriggerEvent::Started, GET_FUNCTION_NAME_CHECKED(AInGameController, OnItemUIEquipItemAction));
	HelperBindInputAction(EnhancedInputComp, InputItemUIUnequipItemAction, ETriggerEvent::Started, GET_FUNCTION_NAME_CHECKED(AInGameController, OnItemUIUnequipItemAction));
	HelperBindInputAction(EnhancedInputComp, InputSettingUIMoveSelectionUp, ETriggerEvent::Started, GET_FUNCTION_NAME_CHECKED(AInGameController, OnSettingUIMoveSelectionUp));
	HelperBindInputAction(EnhancedInputComp, InputSettingUIMoveSelectionDown, ETriggerEvent::Started, GET_FUNCTION_NAME_CHECKED(AInGameController, OnSettingUIMoveSelectionDown));
	HelperBindInputAction(EnhancedInputComp, InputSettingUIMoveSelectionLeft, ETriggerEvent::Started, GET_FUNCTION_NAME_CHECKED(AInGameController, OnSettingUIMoveSelectionLeft));
	HelperBindInputAction(EnhancedInputComp, InputSettingUIMoveSelectionRight, ETriggerEvent::Started, GET_FUNCTION_NAME_CHECKED(AInGameController, OnSettingUIMoveSelectionRight));
	HelperBindInputAction(EnhancedInputComp, InputSettingUIConfirmSelectionAction, ETriggerEvent::Started, GET_FUNCTION_NAME_CHECKED(AInGameController, OnSettingUIConfirmSelectionAction));
	HelperBindInputAction(EnhancedInputComp, InputDialogueUIChangeStoryStateNext, ETriggerEvent::Started, GET_FUNCTION_NAME_CHECKED(AInGameController, OnDialogueUIChangeStoryStateNext));
	HelperBindInputAction(EnhancedInputComp, InputCrackMenuUIBackToCrackMenu, ETriggerEvent::Started, GET_FUNCTION_NAME_CHECKED(AInGameController, OnCrackMenuUIBackToCrackMenu));
	HelperBindInputAction(EnhancedInputComp, InputCrackMenuUIMoveSelectionUp, ETriggerEvent::Started, GET_FUNCTION_NAME_CHECKED(AInGameController, OnCrackMenuUIMoveSelectionUp));
	HelperBindInputAction(EnhancedInputComp, InputCrackMenuUIMoveSelectionDown, ETriggerEvent::Started, GET_FUNCTION_NAME_CHECKED(AInGameController, OnCrackMenuUIMoveSelectionDown));
	HelperBindInputAction(EnhancedInputComp, InputAbilityEnforceUISaveChanges, ETriggerEvent::Started, GET_FUNCTION_NAME_CHECKED(AInGameController, OnAbilityEnforceUISaveChanges));
	HelperBindInputAction(EnhancedInputComp, InputTeleportSubUIMoveSelectionUp, ETriggerEvent::Started, GET_FUNCTION_NAME_CHECKED(AInGameController, OnTeleportSubUISelectionUp));
	HelperBindInputAction(EnhancedInputComp, InputTeleportSubUIMoveSelectionDown, ETriggerEvent::Started, GET_FUNCTION_NAME_CHECKED(AInGameController, OnTeleportSubUISelectionDown));
	HelperBindInputAction(EnhancedInputComp, InputTeleportSubUIMoveSelectionLeft, ETriggerEvent::Started, GET_FUNCTION_NAME_CHECKED(AInGameController, OnTeleportSubUISelectionLeft));
	HelperBindInputAction(EnhancedInputComp, InputTeleportSubUIMoveSelectionRight, ETriggerEvent::Started, GET_FUNCTION_NAME_CHECKED(AInGameController, OnTeleportSubUISelectionRight));
	HelperBindInputAction(EnhancedInputComp, InputTeleportSubUIConfirmSelectionAction, ETriggerEvent::Started, GET_FUNCTION_NAME_CHECKED(AInGameController, OnTeleportSubUIConfirmSelectionAction));
	HelperBindInputAction(EnhancedInputComp, InputPotionEnforceUIEnforceConfirm, ETriggerEvent::Started, GET_FUNCTION_NAME_CHECKED(AInGameController, OnPotionEnforceUIEnforceConfirm));
	
}

#pragma region Input Action Event

void AInGameController::OnMainMenuUIActivateAction() const
{
	OnMainMenuUIActivateActionEvent.Broadcast();
}

void AInGameController::OnMainMenuUIDeactivateAction() const
{
	OnMainMenuUIDeactivateActionEvent.Broadcast();
}

void AInGameController::OnMainMenuUIMoveSelectionLeft() const
{
	OnMainMenuUIMoveSelectionLeftEvent.Broadcast();
}

void AInGameController::OnMainMenuUIMoveSelectionRight() const
{
	OnMainMenuUIMoveSelectionRightEvent.Broadcast();
}

void AInGameController::OnEquipmentUIMoveSelectionUp() const
{
	Debug::Print("EquipmentUIMoveSelectionUp");
	OnEquipmentUIMoveSelectionUpEvent.Broadcast();
}

void AInGameController::OnEquipmentUIMoveSelectionDown() const
{
	Debug::Print("EquipmentUIMoveSelectionDown");
	OnEquipmentUIMoveSelectionDownEvent.Broadcast();
}

void AInGameController::OnEquipmentUIEquipItemAction() const
{
	OnEquipmentUIEquipItemActionEvent.Broadcast();
}

void AInGameController::OnEquipmentUIUnequipItemAction() const
{
	OnEquipmentUIUnequipItemActionEvent.Broadcast();
}

void AInGameController::OnItemUIMoveSelectionUp() const
{
	Debug::Print(TEXT("ItemMoveSelectionUp"));
	OnItemUIMoveSelectionUpEvent.Broadcast();
}

void AInGameController::OnItemUIMoveSelectionDown() const
{
	Debug::Print(TEXT("ItemMoveSelectionDown"));
	OnItemUIMoveSelectionDownEvent.Broadcast();
}

void AInGameController::OnItemUIMoveSelectionLeft() const
{
	Debug::Print(TEXT("ItemMoveSelectionLeft"));
	OnItemUIMoveSelectionLeftEvent.Broadcast();
}

void AInGameController::OnItemUIMoveSelectionRight() const
{
	Debug::Print(TEXT("ItemMoveSelectionRight"));
	OnItemUIMoveSelectionRightEvent.Broadcast();
}

void AInGameController::OnItemUIConsumeItemAction() const
{
	OnItemUIConsumeItemActionEvent.Broadcast();
}

void AInGameController::OnItemUIEquipItemAction() const
{
	OnItemUIEquipItemActionEvent.Broadcast();	
}

void AInGameController::OnItemUIUnequipItemAction() const
{
	OnItemUIUnequipItemActionEvent.Broadcast();
}

void AInGameController::OnSettingUIMoveSelectionUp() const
{
	OnSettingUIMoveSelectionUpEvent.Broadcast();
}

void AInGameController::OnSettingUIMoveSelectionDown() const
{
	OnSettingUIMoveSelectionDownEvent.Broadcast();
}

void AInGameController::OnSettingUIMoveSelectionLeft() const
{
	OnSettingUIMoveSelectionLeftEvent.Broadcast();
}

void AInGameController::OnSettingUIMoveSelectionRight() const
{
	OnSettingUIMoveSelectionRightEvent.Broadcast();
}

void AInGameController::OnSettingUIConfirmSelectionAction() const
{
	OnSettingUIConfirmSelectionActionEvent.Broadcast();
}

void AInGameController::OnDialogueUIChangeStoryStateNext() const
{
	OnDialogueUIChangeStoryStateNextEvent.Broadcast();
}

void AInGameController::OnCrackMenuUIBackToCrackMenu() const
{
	OnCrackMenuUIBackToCrackMenuEvent.Broadcast();
}

void AInGameController::OnCrackMenuUIMoveSelectionUp() const
{
	OnCrackMenuUIMoveSelectionUpEvent.Broadcast();
}

void AInGameController::OnCrackMenuUIMoveSelectionDown() const
{
	OnCrackMenuUIMoveSelectionDownEvent.Broadcast();
}

void AInGameController::OnAbilityEnforceUISaveChanges() const
{
	OnAbilityEnforceUISaveChangesEvent.Broadcast();
}

void AInGameController::OnTeleportSubUISelectionUp() const
{
	OnTeleportSubUISelectionUpEvent.Broadcast();	
}

void AInGameController::OnTeleportSubUISelectionDown() const
{
	OnTeleportSubUISelectionDownEvent.Broadcast();
}

void AInGameController::OnTeleportSubUISelectionLeft() const
{
	OnTeleportSubUISelectionLeftEvent.Broadcast();
}

void AInGameController::OnTeleportSubUISelectionRight() const
{
	OnTeleportSubUISelectionRightEvent.Broadcast();
}

void AInGameController::OnTeleportSubUIConfirmSelectionAction() const
{
	OnTeleportSubUIConfirmSelectionActionEvent.Broadcast();
}

void AInGameController::OnPotionEnforceUIEnforceConfirm() const
{
	OnPotionEnforceUIEnforceConfirmEvent.Broadcast();
}

#pragma endregion

void AInGameController::SetupMappingContext(class UInputMappingContext* NewMappingContext)
{
	if (LocalPlayerInputSubsystem)
	{
		// Mapping Context Add & Remove
		RemoveAllMappingContext();
		if (!LocalPlayerInputSubsystem->HasMappingContext(NewMappingContext))
		{
			LocalPlayerInputSubsystem->AddMappingContext(NewMappingContext, 1);	
		}
		
		// Setting InputMode 
		if (DefaultMappingContext == NewMappingContext)
		{
			const FInputModeGameOnly CurrentInputMode;
			SetInputMode(CurrentInputMode);
			bShowMouseCursor = false;
		}
		else
		{
			const FInputModeGameAndUI CurrentInputMode;
			SetInputMode(CurrentInputMode);
			bShowMouseCursor = true;
		}
	}
}
