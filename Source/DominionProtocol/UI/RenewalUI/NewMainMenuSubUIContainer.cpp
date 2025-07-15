// Fill out your copyright notice in the Description page of Project Settings.


#include "NewMainMenuSubUIContainer.h"

#include "EnhancedInputSubsystems.h"
#include "NewMainMenuButtonContainer.h"
#include "Interface/UIInterface.h"
#include "Player/BasePlayerController.h"

void UNewMainMenuSubUIContainer::ChangeDisplaySubUI(const int32 NewDisplaySubMenuUIIndex)
{
	if (SubUIArray.Num() > 0)
	{
		PushUI(SubUIArray[NewDisplaySubMenuUIIndex]);
	}
	else
	{
		PushUI(StatusSubUI);
	}
}

void UNewMainMenuSubUIContainer::NativeConstruct()
{
	Super::NativeConstruct();

	SubUIArray.AddUnique(StatusSubUI);
	SubUIArray.AddUnique(EquipmentSubUI);
	SubUIArray.AddUnique(ItemSubUI);
	SubUIArray.AddUnique(SettingSubUI);

	ChangeDisplaySubUI(0);
}

void UNewMainMenuSubUIContainer::ChangeMappingContext(UUserWidget* NewTopUI) const
{
	if (ActivatedUIStack.Num() > 0)
	{
		if (NewTopUI && NewTopUI->Implements<UUIInterface>())
		{
			const auto* UIInterface = Cast<IUIInterface>(NewTopUI);
			if (UIInterface)
			{
				const UInputMappingContext* MappingContext = IUIInterface::Execute_GetInputMappingContext(NewTopUI);
				if (MappingContext)
				{
					// MainMenuUI InputMapping 은 Common 으로 사용 중이기에 지우면 안 됨
					// LocalPlayerInputSubsystem->ClearAllMappings();
					LocalPlayerInputSubsystem->AddMappingContext(MappingContext, 10);
				}
				else
				{
					ensureMsgf(MappingContext, TEXT("Failed to load IMC assets. Check connections."));
				}
			}
		}
	}
	else if (ActivatedUIStack.Num() == 0)
	{
		auto* PlayerController = Cast<ABasePlayerController>(GetOwningPlayer());
		if (PlayerController)
		{
			PlayerController->SetupMappingContext();
		}
	}
}

void UNewMainMenuSubUIContainer::BindDisplaySubUIChangedDelegate()
{
	if (MainMenuButtonContainer)
	{
		MainMenuButtonContainer->OnCurrentDisplaySubMenuUIChangedEvent.AddUObject(this, &UNewMainMenuSubUIContainer::ChangeDisplaySubUI);	
	}
}
