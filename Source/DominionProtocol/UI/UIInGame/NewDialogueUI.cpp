// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIInGame/NewDialogueUI.h"

#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "WorldObjects/Crack.h"
#include "WorldObjects/BlockedPath.h"
#include "WorldObjects/DyingHelper.h"
#include "WorldObjects/BossSpawner.h"
#include "WorldObjects/DialogueManager.h"


void UNewDialogueUI::SetDialogueDisplay(const FText NewText)
{
	FullDialogueText = NewText.ToString();
	StartDialogueTyping();
}

UInputMappingContext* UNewDialogueUI::GetInputMappingContext_Implementation() const
{
	if (!DialogueUIMappingContext)
	{
		return nullptr;
	}
	
	return DialogueUIMappingContext;
}

void UNewDialogueUI::NativeConstruct()
{
	Super::NativeConstruct();

	ensureMsgf(DialogueText, TEXT("DialogueText is Null"));
	
	BindCreateDialogueDelegate();
}

void UNewDialogueUI::BindCreateDialogueDelegate()
{
	BindDialogueSources<ACrack>();
	BindDialogueSources<ABlockedPath>();
	BindDialogueSources<ADyingHelper>();
	BindDialogueSources<ABossSpawner>();
}

template<typename T>
void UNewDialogueUI::BindDialogueSources()
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), T::StaticClass(), Actors);

	for (const auto Actor : Actors)
	{
		if (T* TypedActor = Cast<T>(Actor))
		{
			TypedActor->OnCreateDialogueManager.AddUObject(this, &UNewDialogueUI::BindDialogueDelegate);
		}
	}
}

void UNewDialogueUI::BindDialogueDelegate(UDialogueManager* DialogueManager)
{
	DialogueManager->OnUpdateDialogueText.Clear();
	DialogueManager->OnUpdateDialogueText.AddUObject(this, &UNewDialogueUI::SetDialogueDisplay);
}

void UNewDialogueUI::StartDialogueTyping()
{
	if (!DialogueText)
	{
		return;
	}

	CurrentDisplayTextIndex = 0;
	CurrentDisplayText = TEXT("");
	DialogueText->SetText(FText::FromString(CurrentDisplayText));

	if (GetWorld())
	{
		// 이미 실행 중이라면 초기화
		if (GetWorld()->GetTimerManager().IsTimerActive(DialogueTypingTimerHandle))
		{
			GetWorld()->GetTimerManager().ClearTimer(DialogueTypingTimerHandle);
		}

		// 타이머 실행
		GetWorld()->GetTimerManager().SetTimer(
			DialogueTypingTimerHandle,
			this,
			&UNewDialogueUI::TypeNextDialogue,
			DialogueTypingSpeed,
			true
			);
	}
}

void UNewDialogueUI::TypeNextDialogue()
{
	if (!DialogueText)
	{
		return;
	}

	if (CurrentDisplayTextIndex >= FullDialogueText.Len())
	{
		if (GetWorld())
		{
			GetWorld()->GetTimerManager().ClearTimer(DialogueTypingTimerHandle);

			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(
				TimerHandle,
				this,
				&UNewDialogueUI::DialogueTypingFinishedEvent,
				4.0f,
				false
				);
		}
		return;
	}

	CurrentDisplayText += FullDialogueText[CurrentDisplayTextIndex];
	DialogueText->SetText(FText::FromString(CurrentDisplayText));
	CurrentDisplayTextIndex++;
}

void UNewDialogueUI::DialogueTypingFinishedEvent() const
{
	OnDialogueTypingFinishedEvent.Broadcast();
}