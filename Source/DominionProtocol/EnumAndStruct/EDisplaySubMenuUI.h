#pragma once

#include "CoreMinimal.h"
#include "EDisplaySubMenuUI.generated.h"

UENUM(BlueprintType)
enum class EDisplaySubMenuUI : uint8
{
	StatusMenu			UMETA(DisplayName="StatusMenu"),
	EquipmentMenu		UMETA(DisplayName="EquipmentMenu"),
	ItemMenu			UMETA(DisplayName="ItemMenu"),
	SettingMenu			UMETA(DisplayName="SettingMenu"),
	Default				UMETA(DisplayName="Default")
};