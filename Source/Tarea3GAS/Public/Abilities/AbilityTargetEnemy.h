// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityBase_Busy.h"
#include "AbilityTargetEnemy.generated.h"

class UInputAction;

UCLASS()
class TAREA3GAS_API UAbilityTargetEnemy : public UAbilityBase_Busy
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "CancelLockOn") UInputAction* CancelLockOnInput;
	UFUNCTION(Blueprintable,BlueprintCallable, Category = "RotateToTarget") void RotateCharacterToTarget() const;
	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
private:
	AActor* FindEnemyUnderCrosshair(const APlayerController* PC, const FVector& Start, const FVector& End);
	UPROPERTY() AActor* LockedTarget;
	FTimerHandle RotationTimerHandle;
};
