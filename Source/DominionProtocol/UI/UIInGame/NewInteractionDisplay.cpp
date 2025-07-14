// Fill out your copyright notice in the Description page of Project Settings.


#include "NewInteractionDisplay.h"

#include "Components/WidgetComponent/DomiWidgetComponent.h"
#include "Player/Characters/DomiCharacter.h"

void UNewInteractionDisplay::NativeConstruct()
{
	Super::NativeConstruct();

	BindInteractionDelegates();

	OwningCharacter = Cast<ADomiCharacter>(GetOwningPlayerPawn());
}

void UNewInteractionDisplay::UpdateInteractableActorSet(TSet<AActor*> NewInteractableActorSet)
{
	InteractableActorSet = NewInteractableActorSet;
	UpdateInteractionWidget();
}

void UNewInteractionDisplay::UpdateInteractableWidgetFocusing(const float ScrollValue)
{
	ChangeWidgetFocus(ScrollValue);
}

void UNewInteractionDisplay::BindInteractionDelegates()
{
	auto* PlayerCharacter = Cast<ADomiCharacter>(GetOwningPlayerPawn());
	if (PlayerCharacter)
	{
		PlayerCharacter->OnAddInteractableActor.AddUObject(this, &UNewInteractionDisplay::UpdateInteractableActorSet);
		PlayerCharacter->OnRemoveInteractableActor.AddUObject(this, &UNewInteractionDisplay::UpdateInteractableActorSet);
		PlayerCharacter->OnInteractionWidgetScroll.AddUObject(this, &UNewInteractionDisplay::UpdateInteractableWidgetFocusing);
	}
}

void UNewInteractionDisplay::SetInteractableActorEmpty()
{
	ensure(OwningCharacter);

	OwningCharacter->SetCurrentInteractableActor(nullptr);
}


