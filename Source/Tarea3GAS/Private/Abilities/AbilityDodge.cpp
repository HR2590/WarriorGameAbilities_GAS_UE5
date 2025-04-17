// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/AbilityDodge.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "GameFramework/Character.h"

void UAbilityDodge::OnAnimationFinished()
{
	EndPlayAnimTask();
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,false,false);
}


void UAbilityDodge::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
	
	AActor* Avatar=ActorInfo->AvatarActor.Get();
	check(Avatar);
	if(MontageToPlay)
	{
		PlayMontage= UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this,NAME_None,MontageToPlay);
		PlayMontage->OnCompleted.AddDynamic(this,&ThisClass::OnAnimationFinished);
		PlayMontage->OnCancelled.AddDynamic(this,&ThisClass::OnAnimationFinished);
		PlayMontage->OnInterrupted.AddDynamic(this,&ThisClass::OnAnimationFinished);
		PlayMontage->Activate();
	}
	
	ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get());
	APlayerController* PC = Cast<APlayerController>(ActorInfo->PlayerController.Get());

	FVector WorldLocation;
	FVector WorldDirection;

	if (PC&&PC->DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
	{
		FVector TraceStart = WorldLocation;
		FVector TraceEnd = TraceStart + (WorldDirection * 10000.0f);

		FHitResult Hit;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(Character);


		if (Character->GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Visibility, Params))
		{
			FVector Direction = Hit.Location - Character->GetActorLocation();
			Direction.Z = 0;
			Direction.Normalize();
			Character->LaunchCharacter(Direction * DodgeStrength, true, true);
		}
	}
	

}

void UAbilityDodge::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
}
