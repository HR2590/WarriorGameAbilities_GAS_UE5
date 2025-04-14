// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityJump.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "GameFramework/Character.h"

void UAbilityJump::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
	
	AActor* Avatar=GetAvatarActorFromActorInfo();
	check(Avatar);
	if(PlayMontage)
	{
		PlayMontage= UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this,NAME_None,MontageToPlay);
		PlayMontage->OnCompleted.AddDynamic(this,&ThisClass::OnAnimationFinished);
		PlayMontage->OnCancelled.AddDynamic(this,&ThisClass::OnAnimationFinished);
		PlayMontage->OnInterrupted.AddDynamic(this,&ThisClass::OnAnimationFinished);
		PlayMontage->Activate();
	}
	
	Cast<ACharacter>(ActorInfo->AvatarActor)->Jump();
	
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,false,false);
}

void UAbilityJump::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
	
}


void UAbilityJump::OnAnimationFinished()
{
	AActor* Avatar=GetAvatarActorFromActorInfo();
	check(Avatar);
	Cast<ACharacter>(CurrentActorInfo->AvatarActor)->StopJumping();
}
