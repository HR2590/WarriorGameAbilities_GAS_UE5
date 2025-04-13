// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityBase_Busy.h"

UAbilityBase_Busy::UAbilityBase_Busy()
{
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("Character.IsBusy")));
	ActivationOwnedTags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("Character.IsBusy")));
}

void UAbilityBase_Busy::InputPressed(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
}

void UAbilityBase_Busy::InputReleased(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
}
