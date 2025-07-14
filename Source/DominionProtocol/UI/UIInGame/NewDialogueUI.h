// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NewDialogueUI.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDialogueTypingFinishedEvent);

enum class EGameStoryState : uint8;
class UDialogueManager;
class ABossSpawner;
class UTextBlock;

UCLASS()
class DOMINIONPROTOCOL_API UNewDialogueUI : public UUserWidget
{
	GENERATED_BODY()


public:
	FOnDialogueTypingFinishedEvent OnDialogueTypingFinishedEvent;
	
	UFUNCTION()
	void SetDialogueDisplay(const FText NewText);

protected:
	UFUNCTION()
	void StartDialogueTyping();

	UFUNCTION()
	void TypeNextDialogue();

	UFUNCTION()
	void DialogueTypingFinishedEvent() const;
	
	virtual void NativeConstruct() override;

	void BindCreateDialogueDelegate();
	void BindDialogueDelegate(UDialogueManager* DialogueManager);

	template<typename T>
	void BindDialogueSources();

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> DialogueText;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UDialogueManager> CurrentDialogueManager;
	
	FString FullDialogueText;
	FString CurrentDisplayText;
	int32 CurrentDisplayTextIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DialogueTypingSpeed = 0.1f;
	
	FTimerHandle DialogueTypingTimerHandle;
};
