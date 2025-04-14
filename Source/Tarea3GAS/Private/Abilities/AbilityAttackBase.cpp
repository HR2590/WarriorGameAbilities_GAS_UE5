// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityAttackBase.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "DamageCollisionEvaluator.h"
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
	
	PlayMontage= UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this,NAME_None,MontageToPlay);
	PlayMontage->OnCompleted.AddDynamic(this,&ThisClass::OnAnimationFinished);
	PlayMontage->OnCancelled.AddDynamic(this,&ThisClass::OnAnimationFinished);
	PlayMontage->OnInterrupted.AddDynamic(this,&ThisClass::OnAnimationFinished);
	PlayMontage->Activate();
	


}

void UAbilityAttackBase::InputReleased(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,false,false);
	
}


void UAbilityAttackBase::ApplyDamageEffects(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                            UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor&&GameEffect&&OtherActor!=GetAvatarActorFromActorInfo())
	{
		auto ASC= OtherActor->GetComponentByClass<UUTHUB_ASC>();
		if(ASC&&!ASC->GetOwnedGameplayTags().HasTag(FGameplayTag::RequestGameplayTag(TEXT("Character.IsBlocking")))&&GameEffect)
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
	PlayMontage->OnCancelled.Clear();
	PlayMontage->OnInterrupted.Clear();
	PlayMontage->OnCompleted.Clear();
	PlayMontage->EndTask();
	if(const auto CollisionEvaluator=GetAvatarActorFromActorInfo()->FindComponentByClass<UDamageCollisionEvaluator>())
	{
		CollisionEvaluator->OnComponentBeginOverlap.RemoveDynamic(this, &ThisClass::ApplyDamageEffects);
	}
	
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,false,false);
	
}
