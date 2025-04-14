

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AbilityBase_Busy.generated.h"
class UAbilityTask_PlayMontageAndWait;

UCLASS()
class TAREA3GAS_API UAbilityBase_Busy : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UAbilityBase_Busy();
	UPROPERTY(EditAnywhere,Category=GameEffect,meta=(AllowPrivateAccess=true))
	TSubclassOf<UGameplayEffect> GameEffect;
protected:
	UPROPERTY()
	UAbilityTask_PlayMontageAndWait* PlayMontage;
	UPROPERTY(EditAnywhere,Category=Attacks,meta=(AllowPrivateAccess=true))
	UAnimMontage* MontageToPlay;

	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;
	
};
