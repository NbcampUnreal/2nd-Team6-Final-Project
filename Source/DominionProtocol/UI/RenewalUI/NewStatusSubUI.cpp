// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RenewalUI/NewStatusSubUI.h"

#include "NewStatusPlate.h"
#include "DomiFramework/GameInstance/DomiGameInstance.h"
#include "Components/StatusComponent/StatusComponent.h"

void UNewStatusSubUI::SetInfo() const
{
	check(StatusComponent);
	check(DomiGameInstance);

	const TMap<FGameplayTag, float> StatMap = StatusComponent->GetStatMap();
	if (StatMap.Num() > 0)
	{
		// Level Plate
		const float PlayerLevel = *StatMap.Find(StatTags::Level);
		const FText PlayerLevelText = FText::AsNumber(FMath::FloorToInt64(PlayerLevel));

		const float CurrentEssence = FMath::FloorToInt64(DomiGameInstance->GetPlayerCurrentEssence());
		const FText PlayerCurrentEssence = FText::AsNumber(CurrentEssence);

		Level->SetInfo(PlayerLevelText, PlayerCurrentEssence);

		// Attack Plate
		const float PlayerAttackPower = *StatMap.Find(StatTags::AttackPower);
		const FText PlayerAttackPowerText = FText::AsNumber(FMath::RoundToInt64(PlayerAttackPower));
		
		const float PlayerSubAttackPower = *StatMap.Find(StatTags::SubAttackPower);
		const FText PlayerSubAttackPowerText = FText::AsNumber(FMath::RoundToInt64(PlayerSubAttackPower));

		const float PlayerMagicPower = *StatMap.Find(StatTags::MagicPower);
		const FText PlayerMagicPowerText = FText::AsNumber(FMath::RoundToInt64(PlayerMagicPower));

		AttackStatus->SetInfo(PlayerAttackPowerText, PlayerSubAttackPowerText, PlayerMagicPowerText);

		// BaseAbility Plate
		const float PlayerSTR = *StatMap.Find(StatTags::STR);
		const FText PlayerSTRText = FText::AsNumber(FMath::RoundToInt64(PlayerSTR));
		
		const float PlayerSPL = *StatMap.Find(StatTags::SPL);
		const FText PlayerSPLText = FText::AsNumber(FMath::RoundToInt64(PlayerSPL));

		const float PlayerLIFE = *StatMap.Find(StatTags::LIFE);
		const FText PlayerLIFEText = FText::AsNumber(FMath::RoundToInt64(PlayerLIFE));

		const float PlayerEND = *StatMap.Find(StatTags::END);
		const FText PlayerENDText = FText::AsNumber(FMath::RoundToInt64(PlayerEND));

		BaseAbility->SetInfo(PlayerSTRText, PlayerSPLText, PlayerLIFEText, PlayerENDText);

		// BaseStatus Plate
		const float PlayerHealth = *StatMap.Find(StatTags::MaxHealth);
		const FString PlayerHealthString = FString::FormatAsNumber(FMath::RoundToInt64(PlayerHealth));

		const float PlayerMaxHealth = *StatMap.Find(StatTags::MaxHealth);
		const FString PlayerMaxHealthString = FString::FormatAsNumber(FMath::RoundToInt64(PlayerMaxHealth));
		
		const FString PlayerHealthStatString = FString::Printf(TEXT("%s / %s"), *PlayerHealthString, *PlayerMaxHealthString);
		const FText PlayerHealthStatText = FText::FromString(PlayerHealthStatString);

		
		const float PlayerStamina = *StatMap.Find(StatTags::MaxStamina);
		const FString PlayerStaminaString = FString::FormatAsNumber(FMath::RoundToInt64(PlayerStamina));

		const float PlayerMaxStamina = *StatMap.Find(StatTags::MaxStamina);
		const FString PlayerMaxStaminaString = FString::FormatAsNumber(FMath::RoundToInt64(PlayerMaxStamina));
		
		const FString PlayerStaminaStatString = FString::Printf(TEXT("%s / %s"), *PlayerStaminaString, *PlayerMaxStaminaString);
		const FText PlayerStaminaStatText = FText::FromString(PlayerStaminaStatString);
		
		BaseStatus->SetInfo(PlayerHealthStatText, PlayerStaminaStatText);
	}
}

void UNewStatusSubUI::RefreshStatusInfo(const ESlateVisibility NewVisibility)
{
	if (ESlateVisibility::Visible == NewVisibility)
	{
		SetInfo();
	}
}

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

	OnVisibilityChanged.AddDynamic(this, &UNewStatusSubUI::RefreshStatusInfo);
	
	SetInfo();
}
