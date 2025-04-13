

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AbilityBase_Busy.generated.h"


UCLASS()
class TAREA3GAS_API UAbilityBase_Busy : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UAbilityBase_Busy();
	UPROPERTY(EditAnywhere,Category=GameEffect,meta=(AllowPrivateAccess=true))
	TSubclassOf<UGameplayEffect> GameEffect;
protected:

	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	
};
