

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AbilityBase_Busy.generated.h"
class UAbilityTask_PlayMontageAndWait;

UCLASS()
class TAREA3GAS_API UAbilityBase_Busy : public UGameplayAbility
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere,Category=GameEffect,meta=(AllowPrivateAccess=true))
	TSubclassOf<UGameplayEffect> GameEffect;
	
	UPROPERTY()
	UAbilityTask_PlayMontageAndWait* PlayMontage;
	
	UPROPERTY(EditAnywhere,Category=AbilityTask,meta=(AllowPrivateAccess=true))
	UAnimMontage* MontageToPlay;
	
	UFUNCTION(Blueprintable,BlueprintCallable,Category="Abilities|EndAnimationTask")
	void EndPlayAnimTask() const;
	
	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;
	
};
