// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityDefenseBase.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"


void UAbilityDefenseBase::OnAnimationFinished()
{
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,false,false);
}

void UAbilityDefenseBase::CancelAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,false,false);
}


void UAbilityDefenseBase::InputPressed(const FGameplayAbilitySpecHandle Handle,
                                       const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
	AActor* Avatar=ActorInfo->AvatarActor.Get();
	check(Avatar);
	if(MontageToPlay)
	{
		const auto PlayMontage= UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this,NAME_None,MontageToPlay,1.0f,NAME_None,true);
		PlayMontage->OnCompleted.AddDynamic(this,&UAbilityDefenseBase::OnAnimationFinished);
		PlayMontage->OnCancelled.AddDynamic(this,&UAbilityDefenseBase::OnAnimationFinished);
		PlayMontage->OnInterrupted.AddDynamic(this,&UAbilityDefenseBase::OnAnimationFinished);
		PlayMontage->Activate();
	}
	
}

void UAbilityDefenseBase::InputReleased(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
	
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,false,false);
}










