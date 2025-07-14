// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RenewalUI/NewStatusSubUI.h"

#include "DomiFramework/GameInstance/DomiGameInstance.h"
#include "Components/StatusComponent/StatusComponent.h"

void UNewStatusSubUI::NativeConstruct()
{
	Super::NativeConstruct();

	auto* CurrentGameInstance = Cast<UDomiGameInstance>(GetGameInstance());
	if (CurrentGameInstance)
	{
		DomiGameInstance = CurrentGameInstance;
	}

	auto* PlayerStatusComponent = GetOwningPlayerPawn()->GetComponentByClass<UStatusComponent>();
	if (PlayerStatusComponent)
	{
		StatusComponent = PlayerStatusComponent;
	}
}
