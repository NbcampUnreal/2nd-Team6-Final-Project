// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIInGame/NewEventBoxDisplay.h"

#include "Components/TextBlock.h"
#include "Components/ItemComponent/ItemComponent.h"
#include "DomiFramework/GameInstance/DomiGameInstance.h"

void UNewEventBoxDisplay::OnUpdateEventGetEssence(const int32 NewEssence)
{
	UpdateEventGetEssence(NewEssence);
}

void UNewEventBoxDisplay::OnUpdateEventAddItem(const FGameplayTag AddItemTag, const int32 Quantity)
{
	UpdateEventAddItem(AddItemTag, Quantity);
}

void UNewEventBoxDisplay::OnUpdateEventUseItem(const FGameplayTag UseItemTag)
{
	UpdateEventUseItem(UseItemTag);
}

void UNewEventBoxDisplay::NativeConstruct()
{
	Super::NativeConstruct();

	HandleBindEventDelegates();

	for (int32 i = 0; i < WidgetPoolMaxCount; ++i)
	{
		auto* NewEventText = CreateWidget<UUserWidget>(this, EventTextWidgetClass);
		if (NewEventText)
		{
			NewEventText->SetVisibility(ESlateVisibility::Collapsed);
			EventTextPool.Add(NewEventText);
		}
	}
}

void UNewEventBoxDisplay::HandleBindEventDelegates()
{
	auto* DomiGameInstance = Cast<UDomiGameInstance>(GetGameInstance());
	if (DomiGameInstance)
	{
		DomiGameInstance->OnChangedCurrentEssence.AddUObject(this, &UNewEventBoxDisplay::OnUpdateEventGetEssence);
	}

	AActor* PlayerCharacter = GetOwningPlayerPawn();
	if (PlayerCharacter)
	{
		auto* ItemComp = PlayerCharacter->GetComponentByClass<UItemComponent>();
		if (ItemComp)
		{
			ItemComp->OnAddItem.AddUObject(this, &UNewEventBoxDisplay::OnUpdateEventAddItem);
			ItemComp->OnUseItem.AddUObject(this, &UNewEventBoxDisplay::OnUpdateEventUseItem);
		}
	}
}

UUserWidget* UNewEventBoxDisplay::GetEventTextWidgetToPool()
{
	if (EventTextPool.Num() > 0)
	{
		auto* EventText = EventTextPool.Pop();
		ActiveEventTextArray.Add(EventText);
		EventText->SetVisibility(ESlateVisibility::Visible);
		return EventText;
	}

	// EventTextPool.Num() <= 0
	if (EventTextWidgetClass)
	{
		auto* NewEventText = CreateWidget<UUserWidget>(this, EventTextWidgetClass);
		if (NewEventText)
		{
			ActiveEventTextArray.Add(NewEventText);
			return NewEventText;
		}	
	}
	
	return nullptr;
}

void UNewEventBoxDisplay::ReturnEventTextWidgetToPool(class UUserWidget* TextWidget)
{
	if (TextWidget)
	{
		TextWidget->SetVisibility(ESlateVisibility::Collapsed);
		TextWidget->RemoveFromParent();
		ActiveEventTextArray.Remove(TextWidget);
		EventTextPool.Add(TextWidget);
	}
}
