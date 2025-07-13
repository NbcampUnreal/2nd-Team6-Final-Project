// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePlayerController.h"
#include "InGameController.generated.h"

#pragma region ForwardDeclaration

DECLARE_MULTICAST_DELEGATE(FOnSwitchMainMenuUIActivationEvent);
DECLARE_MULTICAST_DELEGATE(FOnMainMenuUIMoveSelectionLeftEvent);
DECLARE_MULTICAST_DELEGATE(FOnMainMenuUIMoveSelectionRightEvent);
DECLARE_MULTICAST_DELEGATE(FOnEquipmentUIMoveSelectionUpEvent);
DECLARE_MULTICAST_DELEGATE(FOnEquipmentUIMoveSelectionDownEvent);
DECLARE_MULTICAST_DELEGATE(FOnEquipmentUIEquipItemActionEvent);
DECLARE_MULTICAST_DELEGATE(FOnEquipmentUIUnequipItemActionEvent);
DECLARE_MULTICAST_DELEGATE(FOnItemUIMoveSelectionUpEvent);
DECLARE_MULTICAST_DELEGATE(FOnItemUIMoveSelectionDownEvent);
DECLARE_MULTICAST_DELEGATE(FOnItemUIMoveSelectionLeftEvent);
DECLARE_MULTICAST_DELEGATE(FOnItemUIMoveSelectionRightEvent);
DECLARE_MULTICAST_DELEGATE(FOnItemUIConsumeItemActionEvent);
DECLARE_MULTICAST_DELEGATE(FOnItemUIEquipItemActionEvent);
DECLARE_MULTICAST_DELEGATE(FOnItemUIUnequipItemActionEvent);
DECLARE_MULTICAST_DELEGATE(FOnSettingUIMoveSelectionUpEvent);
DECLARE_MULTICAST_DELEGATE(FOnSettingUIMoveSelectionDownEvent);
DECLARE_MULTICAST_DELEGATE(FOnSettingUIMoveSelectionLeftEvent);
DECLARE_MULTICAST_DELEGATE(FOnSettingUIMoveSelectionRightEvent);
DECLARE_MULTICAST_DELEGATE(FOnSettingUIConfirmSelectionActionEvent);
DECLARE_MULTICAST_DELEGATE(FOnDialogueUIChangeStoryStateNextEvent);
DECLARE_MULTICAST_DELEGATE(FOnCrackMenuUIBackToCrackMenuEvent);
DECLARE_MULTICAST_DELEGATE(FOnAbilityEnforceUISaveChangesEvent);
DECLARE_MULTICAST_DELEGATE(FOnTeleportSubUISelectionUpEvent);
DECLARE_MULTICAST_DELEGATE(FOnTeleportSubUISelectionDownEvent);
DECLARE_MULTICAST_DELEGATE(FOnTeleportSubUISelectionLeftEvent);
DECLARE_MULTICAST_DELEGATE(FOnTeleportSubUISelectionRightEvent);
DECLARE_MULTICAST_DELEGATE(FOnTeleportSubUIConfirmSelectionActionEvent);
DECLARE_MULTICAST_DELEGATE(FOnPotionEnforceUIEnforceConfirmEvent);

#pragma endregion

class UNewInGameHUDWidget;

UCLASS()
class DOMINIONPROTOCOL_API AInGameController : public ABasePlayerController
{
	GENERATED_BODY()

public:

#pragma region DelegateEvent
	
	FOnSwitchMainMenuUIActivationEvent OnSwitchMainMenuUIActivationEvent;
	FOnMainMenuUIMoveSelectionLeftEvent OnMainMenuUIMoveSelectionLeftEvent;
	FOnMainMenuUIMoveSelectionRightEvent OnMainMenuUIMoveSelectionRightEvent;
	FOnEquipmentUIMoveSelectionUpEvent OnEquipmentUIMoveSelectionUpEvent;
	FOnEquipmentUIMoveSelectionDownEvent OnEquipmentUIMoveSelectionDownEvent;
	FOnEquipmentUIEquipItemActionEvent OnEquipmentUIEquipItemActionEvent;
	FOnEquipmentUIUnequipItemActionEvent OnEquipmentUIUnequipItemActionEvent;
	FOnItemUIMoveSelectionUpEvent OnItemUIMoveSelectionUpEvent;
	FOnItemUIMoveSelectionDownEvent OnItemUIMoveSelectionDownEvent;
	FOnItemUIMoveSelectionLeftEvent OnItemUIMoveSelectionLeftEvent;
	FOnItemUIMoveSelectionRightEvent OnItemUIMoveSelectionRightEvent;
	FOnItemUIConsumeItemActionEvent OnItemUIConsumeItemActionEvent;
	FOnItemUIEquipItemActionEvent OnItemUIEquipItemActionEvent;
	FOnItemUIUnequipItemActionEvent OnItemUIUnequipItemActionEvent;
	FOnSettingUIMoveSelectionUpEvent OnSettingUIMoveSelectionUpEvent;
	FOnSettingUIMoveSelectionDownEvent OnSettingUIMoveSelectionDownEvent;
	FOnSettingUIMoveSelectionLeftEvent OnSettingUIMoveSelectionLeftEvent;
	FOnSettingUIMoveSelectionRightEvent OnSettingUIMoveSelectionRightEvent;
	FOnSettingUIConfirmSelectionActionEvent OnSettingUIConfirmSelectionActionEvent;
	FOnDialogueUIChangeStoryStateNextEvent OnDialogueUIChangeStoryStateNextEvent;
	FOnCrackMenuUIBackToCrackMenuEvent OnCrackMenuUIBackToCrackMenuEvent;
	FOnAbilityEnforceUISaveChangesEvent OnAbilityEnforceUISaveChangesEvent;
	FOnTeleportSubUISelectionUpEvent OnTeleportSubUISelectionUpEvent;
	FOnTeleportSubUISelectionDownEvent OnTeleportSubUISelectionDownEvent;
	FOnTeleportSubUISelectionLeftEvent OnTeleportSubUISelectionLeftEvent;
	FOnTeleportSubUISelectionRightEvent OnTeleportSubUISelectionRightEvent;
	FOnTeleportSubUIConfirmSelectionActionEvent OnTeleportSubUIConfirmSelectionActionEvent;
	FOnPotionEnforceUIEnforceConfirmEvent OnPotionEnforceUIEnforceConfirmEvent;


#pragma endregion
	
	AInGameController();
	
	// 필요시 위젯에서 호출하여 사용
	UFUNCTION(BlueprintCallable)
	void SetupMappingContext(UInputMappingContext* NewMappingContext);
	
	UFUNCTION(BlueprintPure)
	UNewInGameHUDWidget* GetInGameHUDWidget() const { return InGameHUDWidgetInstance; }

	virtual void SetupMappingContext() override;
	
protected:
	virtual void BeginPlay() override;
	
	virtual void CreateAndAddHUDWidget() override;
	virtual void SetupInputMode() override;
	virtual void BindInputActions() override;

#pragma region InputBindingFunction
	
	UFUNCTION()
	void OnSwitchMainMenuUIActivation() const;
	
	UFUNCTION()
	void OnMainMenuUIMoveSelectionLeft() const;
	
	UFUNCTION()
	void OnMainMenuUIMoveSelectionRight() const;
	
	UFUNCTION()
	void OnEquipmentUIMoveSelectionUp() const;
	
	UFUNCTION()
	void OnEquipmentUIMoveSelectionDown() const;
	
	UFUNCTION()
	void OnEquipmentUIEquipItemAction() const;
	
	UFUNCTION()
	void OnEquipmentUIUnequipItemAction() const;
	
	UFUNCTION()
	void OnItemUIMoveSelectionUp() const;
	
	UFUNCTION()
	void OnItemUIMoveSelectionDown() const;
	
	UFUNCTION()
	void OnItemUIMoveSelectionLeft() const;
	
	UFUNCTION()
	void OnItemUIMoveSelectionRight() const;
	
	UFUNCTION()
	void OnItemUIConsumeItemAction() const;
	
	UFUNCTION()
	void OnItemUIEquipItemAction() const;
	
	UFUNCTION()
	void OnItemUIUnequipItemAction() const;
	
	UFUNCTION()
	void OnSettingUIMoveSelectionUp() const;
	
	UFUNCTION()
	void OnSettingUIMoveSelectionDown() const;
	
	UFUNCTION()
	void OnSettingUIMoveSelectionLeft() const;
	
	UFUNCTION()
	void OnSettingUIMoveSelectionRight() const;
	
	UFUNCTION()
	void OnSettingUIConfirmSelectionAction() const;
	
	UFUNCTION()
	void OnDialogueUIChangeStoryStateNext() const;
	
	UFUNCTION()
	void OnCrackMenuUIBackToCrackMenu() const;
	
	UFUNCTION()
	void OnAbilityEnforceUISaveChanges() const;
	
	UFUNCTION()
	void OnTeleportSubUISelectionUp() const;
	
	UFUNCTION()
	void OnTeleportSubUISelectionDown() const;
	
	UFUNCTION()
	void OnTeleportSubUISelectionLeft() const;
	
	UFUNCTION()
	void OnTeleportSubUISelectionRight() const;
	
	UFUNCTION()
	void OnTeleportSubUIConfirmSelectionAction() const;
	
	UFUNCTION()
	void OnPotionEnforceUIEnforceConfirm() const;

#pragma endregion

#pragma region CharacterInput
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> DashAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> SprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ParryAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> BaseAttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> WeaponSkillAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MagicSkillAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LockOnAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ConsumeItemAction_1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ConsumeItemAction_2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ConsumeItemAction_3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> SwapWeapon;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InteractionScroll;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InteractAction;
	
#pragma endregion
	
#pragma region UIInput

	// MainMenuUI Common Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InputSwitchMainMenuUIActivation;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InputMainMenuUIMoveSelectionLeft;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InputMainMenuUIMoveSelectionRight;


	// EquipmentSubUI Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InputEquipmentUIMoveSelectionUp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InputEquipmentUIMoveSelectionDown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InputEquipmentUIEquipItemAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InputEquipmentUIUnequipItemAction;


	// ItemSubUI Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InputItemUIMoveSelectionUp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InputItemUIMoveSelectionDown;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InputItemUIMoveSelectionLeft;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InputItemUIMoveSelectionRight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InputItemUIConsumeItemAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InputItemUIEquipItemAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InputItemUIUnequipItemAction;

	
	// SettingSubUI Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InputSettingUIMoveSelectionUp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InputSettingUIMoveSelectionDown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InputSettingUIMoveSelectionLeft;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InputSettingUIMoveSelectionRight;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InputSettingUIConfirmSelectionAction;
	
	
	// DialogueUI Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InputDialogueUIChangeStoryStateNext;


	// CrackMenuUI Common Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InputCrackMenuUIBackToCrackMenu;

	// AbilityEnforceSubUI InputAction

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InputAbilityEnforceUISaveChanges;

	// TeleportCrackSubUI InputAction

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InputTeleportSubUISelectionUp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InputTeleportSubUISelectionDown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InputTeleportSubUISelectionLeft;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InputTeleportSubUISelectionRight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InputTeleportSubUIConfirmSelectionAction;

	// PotionEnforceSubUI InputAction

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InputPotionEnforceUIEnforceConfirm;
	
#pragma endregion
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UNewInGameHUDWidget> InGameHUDWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UNewInGameHUDWidget> InGameHUDWidgetInstance;
	
};
