// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIInGame/NewAlertUI.h"

#include "AI/AICharacters/BossMonster/BaseBossEnemy.h"
#include "Components/TextBlock.h"
#include "Components/StatusComponent/StatusComponent.h"
#include "DomiFramework/GameMode/BaseGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "WorldObjects/Crack.h"
#include "WorldObjects/DropEssence.h"

void UNewAlertUI::OnShowPlayerDeathAlert() const
{
	const FText AlertTextToText = FText::FromString(FString(TEXT("플레이어 사망"))); 
	AlertText->SetText(AlertTextToText);
}

void UNewAlertUI::OnShowBossKillAlert(AActor* DeadMonster) const
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
}

void UNewAlertUI::OnShowEssenceRestoredAlert(const int32 NewEssenceAmount) const
{
	const FText AlertTextToText = FText::FromString(FString::Printf(TEXT("균열 정수 %d 회복 "), NewEssenceAmount));
	AlertText->SetText(AlertTextToText);
	
	// 에센스 획득 후 델리게이트 핸들 삭제, 에센스 자체에 있는 델리게이트는 파괴시 삭제되지만 이 경우엔 명시적으로 삭제해주면 좋음
	auto* InGameMode = Cast<ABaseGameMode>(GetWorld()->GetAuthGameMode());
	if (InGameMode)
	{
		InGameMode->OnSpawnDropEssence.Remove(HandleBindRestoredEssence);
	}
}

void UNewAlertUI::OnShowCrackActivationAlert(const FText CrackName) const
{
	const FText AlertTextToText = FText::FromString(FString::Printf(TEXT("균열 %s 활성화"), *CrackName.ToString()));
	AlertText->SetText(AlertTextToText);
}

void UNewAlertUI::StartAlertUIDeactivateTimer()
{
	if (GetWorld())
	{
		if (GetWorld()->GetTimerManager().IsTimerActive(AlertUIDeactivateTimer))
		{
			GetWorld()->GetTimerManager().ClearTimer(AlertUIDeactivateTimer);
		}

		GetWorld()->GetTimerManager().SetTimer(
			AlertUIDeactivateTimer,
			this,
			&UNewAlertUI::DeactivateAlertUIEvent,
			4.f,
			false);
	}
}

void UNewAlertUI::DeactivateAlertUIEvent() const
{
	OnAlertDisplayFinishedEvent.Broadcast();
}

void UNewAlertUI::NativeConstruct()
{
	Super::NativeConstruct();

	BindAlertDelegates();
}

void UNewAlertUI::BindAlertDelegates()
{
	// 균열 활성화 바인딩 섹션
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACrack::StaticClass(), FoundActors);

	for (auto* Actor : FoundActors)
	{
		auto* Crack = Cast<ACrack>(Actor);
		if (Crack)
		{
			Crack->OnActiveCrack.AddUObject(this, &UNewAlertUI::OnShowCrackActivationAlert);
		}
	}

	// 플레이어 데스 바인딩 섹션
	auto* StatusComponent = GetOwningPlayerPawn()->GetComponentByClass<UStatusComponent>();
	if (StatusComponent)
	{
		StatusComponent->OnDeath.AddUObject(this, &UNewAlertUI::OnShowPlayerDeathAlert);
	}

	// 보스 사망 및 DropEssence 바인딩 섹션
	auto* InGameMode = Cast<ABaseGameMode>(GetWorld()->GetAuthGameMode());
	if (InGameMode)
	{
		InGameMode->OnEndBattle.AddUObject(this, &UNewAlertUI::OnShowBossKillAlert);
		HandleBindRestoredEssence = InGameMode->OnSpawnDropEssence.AddUObject(this, &UNewAlertUI::BindRestoredEssence);
	}
}

void UNewAlertUI::BindRestoredEssence(class ADropEssence* DropEssence)
{
	DropEssence->OnDropEssenceRestored.AddUObject(this, &UNewAlertUI::OnShowEssenceRestoredAlert);
}