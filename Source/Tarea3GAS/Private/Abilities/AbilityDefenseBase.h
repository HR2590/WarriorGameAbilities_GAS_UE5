// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityBase_Busy.h"
#include "AbilityDefenseBase.generated.h"


UCLASS()
class TAREA3GAS_API UAbilityDefenseBase : public UAbilityBase_Busy
{
	GENERATED_BODY()

protected:
	UFUNCTION()void OnAnimationFinished();
	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;
	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
private:
	UPROPERTY(EditAnywhere,Category=Attacks,meta=(AllowPrivateAccess=true))UAnimMontage* MontageToPlay;
	
};
