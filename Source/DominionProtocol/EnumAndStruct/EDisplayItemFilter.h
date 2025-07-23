#pragma once

#include "CoreMinimal.h"
#include "EDisplayItemFilter.generated.h"

UENUM(BlueprintType)
enum class EDisplayItemFilter : uint8
{
	AllItems				UMETA(DisplayName="모든 아이템"),
	WeaponItems				UMETA(DisplayName="무기 아이템"),
	AccessoryItems			UMETA(DisplayName="장신구 아이템"),
	ConsumableItems			UMETA(DisplayName="소모품 아이템"),
	SkillItems				UMETA(DisplayName="스킬 아이템"),
	OtherItems				UMETA(DisplayName="기타 아이템"),
};
