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
	
	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;
private:
	UFUNCTION()
	void ApplyDamageEffects(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UPROPERTY(EditAnywhere,Category=Attacks,meta=(AllowPrivateAccess=true))UAnimMontage* MontageToPlay;

	UFUNCTION()void OnAnimationFinished();
};


