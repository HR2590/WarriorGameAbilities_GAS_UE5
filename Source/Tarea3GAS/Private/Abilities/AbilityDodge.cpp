// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityDodge.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"

void UAbilityDodge::OnAnimationFinished()
{
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,false,false);
}

void UAbilityDodge::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,false,false);
}

void UAbilityDodge::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
	
	AActor* Avatar=ActorInfo->AvatarActor.Get();
	check(Avatar);
	const auto PlayMontage= UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this,NAME_None,MontageToPlay,1.0f,NAME_None,true);
	PlayMontage->OnCompleted.AddDynamic(this,&ThisClass::OnAnimationFinished);
	PlayMontage->OnCancelled.AddDynamic(this,&ThisClass::OnAnimationFinished);
	PlayMontage->OnInterrupted.AddDynamic(this,&ThisClass::OnAnimationFinished);
	PlayMontage->Activate();
}

void UAbilityDodge::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
}
