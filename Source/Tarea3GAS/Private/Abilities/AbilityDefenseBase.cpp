// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityDefenseBase.h"

#include "UTHUB_ASC.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "Engine/SpecularProfile.h"
#include "GameFramework/Character.h"


void UAbilityDefenseBase::OnAnimationFinished()
{
	PlayMontage->OnCancelled.Clear();
	PlayMontage->OnInterrupted.Clear();
	PlayMontage->OnCompleted.Clear();
	PlayMontage->EndTask();
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
		PlayMontage= UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this,NAME_None,MontageToPlay,1.0f,NAME_Default,false);
		PlayMontage->OnCompleted.AddDynamic(this,&UAbilityDefenseBase::OnAnimationFinished);
		PlayMontage->OnCancelled.AddDynamic(this,&UAbilityDefenseBase::OnAnimationFinished);
		PlayMontage->OnInterrupted.AddDynamic(this,&UAbilityDefenseBase::OnAnimationFinished);
		PlayMontage->ReadyForActivation();
		
	}
	PlayMontage->EndTask();

	
	auto ASC=GetAvatarActorFromActorInfo()->FindComponentByClass<UUTHUB_ASC>();

	if(!ASC->GetActiveGameplayEffect(AbilitySpecHandle))
	{
		AbilitySpecHandle=ASC->ApplyEffectFromClassToTarget(GameEffect);
	}
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,false,false);
	
}

void UAbilityDefenseBase::InputReleased(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
	AActor* Avatar=ActorInfo->AvatarActor.Get();
	check(Avatar);
	UAnimInstance* AnimInstance = Cast<ACharacter>(Avatar)->GetMesh()->GetAnimInstance();
	if (AnimInstance && AnimInstance->Montage_IsPlaying(MontageToPlay))
	{
		AnimInstance->Montage_Stop(0.5f, MontageToPlay);
	}
	
	auto ASC=GetAvatarActorFromActorInfo()->FindComponentByClass<UUTHUB_ASC>();
	ASC->RemoveActiveGameplayEffect(AbilitySpecHandle);
	
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,false,false);
}












