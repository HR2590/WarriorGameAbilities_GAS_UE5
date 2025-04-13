#pragma once

#include "EAbilityInputID.generated.h"


UENUM(BlueprintType)
enum class EAbilityInputID : uint8
{
	Attack      UMETA(DisplayName = "Attack"),
	Defend      UMETA(DisplayName = "Defend"),
	Dodge		UMETA(DisplayName = "Dodge"),
	Celebrate	UMETA(DisplayName = "Celebrate"),
	Target      UMETA(DisplayName = "Target"),
	Jump		UMETA(DisplayName = "Jump"),

};
