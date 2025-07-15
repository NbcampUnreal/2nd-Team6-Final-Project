// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIInGame/NewAlertDisplay.h"

#include "AI/AICharacters/BossMonster/BaseBossEnemy.h"
#include "Components/TextBlock.h"
#include "Components/StatusComponent/StatusComponent.h"
#include "DomiFramework/GameMode/BaseGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "WorldObjects/Crack.h"
#include "WorldObjects/DropEssence.h"

void UNewAlertDisplay::OnShowPlayerDeathAlert()
{
	const FText AlertTextToText = FText::FromString(FString(TEXT("플레이어 사망"))); 
	AlertText->SetText(AlertTextToText);
	SetVisibility(ESlateVisibility::Visible);
}

void UNewAlertDisplay::OnShowBossKillAlert(AActor* DeadMonster) 
{
	FString MonsterName;
	
	const auto* BossEnemy = Cast<ABaseBossEnemy>(DeadMonster);
	if (BossEnemy)
	{
		MonsterName = BossEnemy->GetMonsterName();
		const TCHAR LastChar = MonsterName.GetCharArray()[MonsterName.Len()-1];
		if (LastChar >= 0xAC00 && LastChar <= 0xD7A3)
		{
			if (((LastChar- 0xAC00) % 28) != 0)
			{
				MonsterName = MonsterName + TEXT("을");
			}
			else
			{
				MonsterName = MonsterName + TEXT("를");
			}
		}
		else
		{
			MonsterName = MonsterName + TEXT("를");
		}
	}
	
	const FText AlertTextToText = FText::FromString(FString::Printf(TEXT("%s 처치"), *MonsterName));
	AlertText->SetText(AlertTextToText);
	SetVisibility(ESlateVisibility::Visible);
}

void UNewAlertDisplay::OnShowEssenceRestoredAlert(const int32 NewEssenceAmount) 
{
	const FText AlertTextToText = FText::FromString(FString::Printf(TEXT("균열 정수 %d 회복 "), NewEssenceAmount));
	AlertText->SetText(AlertTextToText);
	SetVisibility(ESlateVisibility::Visible);
	
	// 에센스 획득 후 델리게이트 핸들 삭제, 에센스 자체에 있는 델리게이트는 파괴시 삭제되지만 이 경우엔 명시적으로 삭제해주면 좋음
	auto* InGameMode = Cast<ABaseGameMode>(GetWorld()->GetAuthGameMode());
	if (InGameMode)
	{
		InGameMode->OnSpawnDropEssence.Remove(HandleBindRestoredEssence);
	}
}

void UNewAlertDisplay::OnShowCrackActivationAlert(const FText CrackName) 
{
	const FText AlertTextToText = FText::FromString(FString::Printf(TEXT("균열 %s 활성화"), *CrackName.ToString()));
	AlertText->SetText(AlertTextToText);
	SetVisibility(ESlateVisibility::Visible);
}

void UNewAlertDisplay::StartAlertDisplayDeactivateTimer()
{
	if (GetWorld())
	{
		if (GetWorld()->GetTimerManager().IsTimerActive(AlertDisplayDeactivateTimer))
		{
			GetWorld()->GetTimerManager().ClearTimer(AlertDisplayDeactivateTimer);
		}

		GetWorld()->GetTimerManager().SetTimer(
			AlertDisplayDeactivateTimer,
			[this]()
			{
				SetVisibility(ESlateVisibility::Collapsed);	
			},
			4.f,
			false);
	}
}

void UNewAlertDisplay::NativeConstruct()
{
	Super::NativeConstruct();

	BindAlertDelegates();
}

void UNewAlertDisplay::BindAlertDelegates()
{
	// 균열 활성화 바인딩 섹션
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACrack::StaticClass(), FoundActors);

	for (auto* Actor : FoundActors)
	{
		auto* Crack = Cast<ACrack>(Actor);
		if (Crack)
		{
			Crack->OnActiveCrack.AddUObject(this, &UNewAlertDisplay::OnShowCrackActivationAlert);
		}
	}

	// 플레이어 데스 바인딩 섹션
	auto* StatusComponent = GetOwningPlayerPawn()->GetComponentByClass<UStatusComponent>();
	if (StatusComponent)
	{
		StatusComponent->OnDeath.AddUObject(this, &UNewAlertDisplay::OnShowPlayerDeathAlert);
	}

	// 보스 사망 및 DropEssence 바인딩 섹션
	auto* InGameMode = Cast<ABaseGameMode>(GetWorld()->GetAuthGameMode());
	if (InGameMode)
	{
		InGameMode->OnEndBattle.AddUObject(this, &UNewAlertDisplay::OnShowBossKillAlert);
		HandleBindRestoredEssence = InGameMode->OnSpawnDropEssence.AddUObject(this, &UNewAlertDisplay::BindRestoredEssence);
	}
}

void UNewAlertDisplay::BindRestoredEssence(class ADropEssence* DropEssence)
{
	DropEssence->OnDropEssenceRestored.AddUObject(this, &UNewAlertDisplay::OnShowEssenceRestoredAlert);
}