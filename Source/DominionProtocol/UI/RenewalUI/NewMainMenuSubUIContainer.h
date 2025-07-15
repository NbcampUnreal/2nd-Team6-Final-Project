// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnumAndStruct/EDisplaySubMenuUI.h"
#include "UI/BaseHUDWidget.h"
#include "NewMainMenuSubUIContainer.generated.h"

class UNewMainMenuButtonContainer;

UCLASS()
class DOMINIONPROTOCOL_API UNewMainMenuSubUIContainer : public UBaseHUDWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void SetMainMenuButtonContainer(UNewMainMenuButtonContainer* NewMainMenuButtonContainer) { MainMenuButtonContainer = NewMainMenuButtonContainer;}

protected:
	void ChangeDisplaySubUI(const EDisplaySubMenuUI NewDisplaySubMenuUI);
	
	virtual void NativeConstruct() override;

	UFUNCTION()
	void BindDisplaySubUIChangedDelegate();
	
protected:
	UPROPERTY()
	TObjectPtr<UNewMainMenuButtonContainer> MainMenuButtonContainer;

	UPROPERTY()
	TArray<TObjectPtr<UUserWidget>> SubUIArray;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UUserWidget> StatusSubUI;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UUserWidget> EquipmentSubUI;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UUserWidget> ItemSubUI;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UUserWidget> SettingSubUI;
	
};
