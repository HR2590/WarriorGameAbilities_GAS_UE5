// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityBase_Busy.h"
#include "AbilityAttackBase.generated.h"

/**
 * 
 */
UCLASS()
class TAREA3GAS_API UAbilityAttackBase : public UAbilityBase_Busy
{
	GENERATED_BODY()
protected:
	
	virtual void InputPressed(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo) override;
	
	UFUNCTION(Blueprintable,BlueprintCallable,Category="Abilities|ApplyDamageEffect")
	void ApplyDamageEffects(
		UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);
	
	UFUNCTION(Blueprintable,BlueprintCallable,Category="Abilities|OnAnimationFinished")
	void OnAnimationFinished();
};


