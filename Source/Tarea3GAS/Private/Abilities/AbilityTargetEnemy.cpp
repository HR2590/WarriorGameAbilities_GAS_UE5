// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AbilityTargetEnemy.h"
#include "Abilities/Tasks/AbilityTask_WaitInputPress.h"
#include "GASDataComponent.h"
#include "GameFramework/Character.h"



void UAbilityTargetEnemy::RotateCharacterToTarget() const
{
	if (!CurrentActorInfo || !CurrentActorInfo->AvatarActor.IsValid() || !LockedTarget) return;

	ACharacter* Character = Cast<ACharacter>(CurrentActorInfo->AvatarActor.Get());
	if (!Character) return;

	FVector Direction = LockedTarget->GetActorLocation() - Character->GetActorLocation();
	FRotator LookAtRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
	LookAtRotation.Pitch = 0;
	LookAtRotation.Roll = 0;

	Character->SetActorRotation(FMath::RInterpTo(Character->GetActorRotation(), LookAtRotation, GetWorld()->GetDeltaSeconds(), 8.f));
}


void UAbilityTargetEnemy::InputPressed(const FGameplayAbilitySpecHandle Handle,
                                       const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
	RotationTimerHandle.Invalidate();
	LockedTarget=nullptr;
	APlayerController* PC = Cast<APlayerController>(ActorInfo->PlayerController.Get());
	APawn* Avatar = Cast<APawn>(ActorInfo->AvatarActor.Get());

	if (!PC || !Avatar)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	FVector Start, Dir;
	PC->DeprojectMousePositionToWorld(Start, Dir);

	FVector End = Start + Dir * 50000.f;
	LockedTarget = FindEnemyUnderCrosshair(PC, Start, End);
	if (LockedTarget)
	{
		Avatar->GetWorldTimerManager().SetTimer(
			RotationTimerHandle,
			this,
			&ThisClass::RotateCharacterToTarget,
			0.01f, 
			true);
	}

}



AActor* UAbilityTargetEnemy::FindEnemyUnderCrosshair(const APlayerController* PC, const FVector& Start,
	const FVector& End)
{
	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(PC->GetPawn());

	bool bHit = PC->GetWorld()->LineTraceSingleByChannel(
		Hit,
		Start,
		End,
		ECC_Pawn,
		Params
	);

	if (bHit && Hit.GetActor())
	{
		AActor* HitActor = Hit.GetActor();

		if (auto Data=HitActor->FindComponentByClass<UGASDataComponent>())
		{
			return HitActor;
		}
	}

	return nullptr;
}
