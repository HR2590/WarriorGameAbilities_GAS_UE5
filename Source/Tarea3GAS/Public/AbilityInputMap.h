#pragma once
#include "Abilities/GameplayAbility.h"
#include  "AbilityInputMap.generated.h"
class UInputAction;


USTRUCT(BlueprintType,Blueprintable)
struct FAbilityInputMap
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Mappings)
	TMap<UInputAction*,TSubclassOf<UGameplayAbility>> AbilityMap;
	
};
