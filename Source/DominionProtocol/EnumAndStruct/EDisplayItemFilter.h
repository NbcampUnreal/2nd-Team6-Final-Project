#pragma once

#include "CoreMinimal.h"
#include "EDisplayItemFilter.generated.h"

UENUM(BlueprintType)
enum class EDisplayItemFilter : uint8
{
	AllItems				UMETA(DisplayName="AllItems"),
	WeaponItems				UMETA(DisplayName="WeaponItems"),
	AccessoryItems			UMETA(DisplayName="AccessoryItems"),
	ConsumableItems			UMETA(DisplayName="ConsumableItems"),
	SkillItems				UMETA(DisplayName="SkillItems"),
	OtherItems				UMETA(DisplayName="OtherItems"),
};
