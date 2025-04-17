// Fill out your copyright notice in the Description page of Project Settings.
#include "Abilities/AbilityAttackBase.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "DamageCollisionEvaluator.h"
#include "FGameplayTagsManager.h"
#include "UTHUB_ASC.h"

void UAbilityAttackBase::InputPressed(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
	
	AActor* Avatar=ActorInfo->AvatarActor.Get();
	check(Avatar);
	
	if(const auto CollisionEvaluator=Avatar->FindComponentByClass<UDamageCollisionEvaluator>())
	{
		CollisionEvaluator->OnComponentBeginOverlap.RemoveDynamic(this, &ThisClass::ApplyDamageEffects);
		CollisionEvaluator->OnComponentBeginOverlap.AddDynamic(this,&ThisClass::ApplyDamageEffects);
	}
	
	if(MontageToPlay)
	{
		PlayMontage= UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this,NAME_None,MontageToPlay);
		PlayMontage->OnCompleted.AddDynamic(this,&ThisClass::OnAnimationFinished);
		PlayMontage->OnCancelled.AddDynamic(this,&ThisClass::OnAnimationFinished);
		PlayMontage->OnInterrupted.AddDynamic(this,&ThisClass::OnAnimationFinished);
		PlayMontage->Activate();
	}

	
}

void UAbilityAttackBase::ApplyDamageEffects(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                            UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor&&GameEffect&&OtherActor!=GetAvatarActorFromActorInfo())
	{
		const auto ASC= OtherActor->GetComponentByClass<UUTHUB_ASC>();
		if(ASC&&!ASC->GetOwnedGameplayTags().HasTag(FGameplayTagsManager::Get().IsBlocking)&&GameEffect)
		{
			OtherActor->GetComponentByClass<UUTHUB_ASC>()->ApplyEffectFromClassToTarget(GameEffect);
			if(const auto CollisionEvaluator=GetAvatarActorFromActorInfo()->FindComponentByClass<UDamageCollisionEvaluator>())
			{
				CollisionEvaluator->OnComponentBeginOverlap.RemoveDynamic(this, &ThisClass::ApplyDamageEffects);
			}
		}
		
	}
	
}

void UAbilityAttackBase::OnAnimationFinished()
{
	EndPlayAnimTask();

	if(const auto CollisionEvaluator=GetAvatarActorFromActorInfo()->FindComponentByClass<UDamageCollisionEvaluator>())
	{
		CollisionEvaluator->OnComponentBeginOverlap.RemoveDynamic(this, &ThisClass::ApplyDamageEffects);
	}
	
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,false,false);
	
}
