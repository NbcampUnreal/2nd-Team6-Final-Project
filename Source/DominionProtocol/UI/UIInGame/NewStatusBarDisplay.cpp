// Fill out your copyright notice in the Description page of Project Settings.


#include "NewStatusBarDisplay.h"

#include "Components/StatusComponent/StatusComponent.h"
#include "Player/Characters/DomiCharacter.h"

void UNewStatusBarDisplay::NativeConstruct()
{
	Super::NativeConstruct();

	// Check Widget Binding 
	ensure(PlayerHPBar);
	ensure(PlayerStaminaBar);

	// Initialize & DelegateBinding
	AActor* OwningActor = GetOwningPlayerPawn();
	if (OwningActor)
	{
		SetupStatusBarWidget(OwningActor);
	}
}

void UNewStatusBarDisplay::UpdatePlayerHPBar(const float NewHP)
{
	AlphaForHPAnim = 0.0f;
	PreHP = CurrentHP;
	CurrentHP = NewHP;
}

void UNewStatusBarDisplay::UpdatePlayerMaxHPBar(const float NewMaxHP)
{
	AlphaForHPAnim = 0.0f;
	PreMaxHP = MaxHP;
	MaxHP = NewMaxHP;
}

void UNewStatusBarDisplay::UpdatePlayerStaminaBar(const float NewStamina)
{
	AlphaForStaminaAnim = 0.0f;
	PreStamina = CurrentStamina;
	CurrentStamina = NewStamina;
}

void UNewStatusBarDisplay::UpdatePlayerMaxStaminaBar(const float NewMaxStamina)
{
	AlphaForStaminaAnim = 0.0f;
	PreStamina = MaxStamina;
	MaxStamina = NewMaxStamina;
}

void UNewStatusBarDisplay::OnUpdateEffectUIDataArray(TArray<FEffectUIData> NewEffectUIDataArray)
{
	TArray<FEffectUIData> TempBuffArray;
	TArray<FEffectUIData> TempDebuffArray;
	
	for (auto EffectData:NewEffectUIDataArray)
	{
		if (EffectData.EffectTag.MatchesTag(EffectTags::ControlBuff) || EffectData.EffectTag.MatchesTag(EffectTags::StatusBuff))
		{
			TempBuffArray.Add(EffectData);		
		}

		if (EffectData.EffectTag.MatchesTag(EffectTags::ControlDebuff) || EffectData.EffectTag.MatchesTag(EffectTags::StatusDebuff))
		{
			TempDebuffArray.Add(EffectData);
		}
	}

	BuffEffectUIDataArray = TempBuffArray;
	DebuffEffectUIDataArray = TempDebuffArray;

	UpdateEffectUIDataArray();
}

void UNewStatusBarDisplay::SetupStatusBarWidget(AActor* OwningActor)
{
	ensure(IsValid(OwningActor));
	
	auto* StatusComp = OwningActor->GetComponentByClass<UStatusComponent>();
	if (StatusComp)
	{
		// Initialize 
		MaxHP = StatusComp->GetStat(StatTags::MaxHealth);
		MaxStamina = StatusComp->GetStat(StatTags::MaxStamina);
		CurrentHP = StatusComp->GetStat(StatTags::Health);
		CurrentStamina = StatusComp->GetStat(StatTags::Stamina);

		// Delegate Binding
		StatusComp->OnHealthChanged.AddDynamic(this, &UNewStatusBarDisplay::UpdatePlayerHPBar);
		StatusComp->OnStaminaChanged.AddDynamic(this, &UNewStatusBarDisplay::UpdatePlayerStaminaBar);
		StatusComp->OnMaxHealthChanged.AddDynamic(this, &UNewStatusBarDisplay::UpdatePlayerMaxHPBar);
		StatusComp->OnMaxStaminaChanged.AddDynamic(this, &UNewStatusBarDisplay::UpdatePlayerMaxStaminaBar);
	}
	
	auto* PlayerCharacter = Cast<ADomiCharacter>(OwningActor);
	if (PlayerCharacter)
	{
		PlayerCharacter->OnUpdateEffectUIDataArray.AddUObject(this, &UNewStatusBarDisplay::OnUpdateEffectUIDataArray);
	}
}
