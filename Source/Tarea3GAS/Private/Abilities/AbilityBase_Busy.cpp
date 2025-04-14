// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityBase_Busy.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"


UAbilityBase_Busy::UAbilityBase_Busy()
{
}

void UAbilityBase_Busy::CancelAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
 	if(PlayMontage)
	{
		PlayMontage->OnCancelled.Clear();
		PlayMontage->OnInterrupted.Clear();
		PlayMontage->OnCompleted.Clear();
 		PlayMontage->OnBlendOut.Clear();
		PlayMontage->EndTask();
	}
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,false,false);
}
