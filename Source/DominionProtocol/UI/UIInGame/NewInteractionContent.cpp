// Fill out your copyright notice in the Description page of Project Settings.


#include "NewInteractionContent.h"

#include "Player/Characters/DomiCharacter.h"

void UNewInteractionContent::SetReceivedInteractableActor(AActor* Actor = nullptr)
{
	ReceivedInteractableActor = Actor;
	OwningCharacter->SetCurrentInteractableActor(ReceivedInteractableActor);
}

void UNewInteractionContent::NativeConstruct()
{
	Super::NativeConstruct();

	OwningCharacter = Cast<ADomiCharacter>(GetOwningPlayerPawn());
}
