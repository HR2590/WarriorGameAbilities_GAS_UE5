// Fill out your copyright notice in the Description page of Project Settings.


#include "UTHUB_ASC.h"

#include "CoreAttributeSet.h"
#include "GASDataComponent.h"


// Sets default values for this component's properties
UUTHUB_ASC::UUTHUB_ASC()
{

	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UUTHUB_ASC::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo(GetOwner(),GetOwner());
	
}


void UUTHUB_ASC::InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor)
{
	Super::InitAbilityActorInfo(InOwnerActor, InAvatarActor);
	

	InitializeAttributesFromEffects();
}

FGameplayEffectSpec* UUTHUB_ASC::MakeSpec(const TSubclassOf<UGameplayEffect>& EffectClass,int InLevel) const
{

	FGameplayEffectContextHandle EffectContext=MakeEffectContext();
	EffectContext.AddSourceObject(this);
	return MakeOutgoingSpec(EffectClass,InLevel,EffectContext).Data.Get();

}


FActiveGameplayEffectHandle UUTHUB_ASC::ApplyEffectFromClassToTarget(const TSubclassOf<UGameplayEffect>& EffectClass)
{
	check(EffectClass)
	return ApplyGameplayEffectSpecToTarget(*MakeSpec(EffectClass,1),this);

}

FActiveGameplayEffectHandle UUTHUB_ASC::ApplyEffectFromClassToSelf(const TSubclassOf<UGameplayEffect>& EffectClass)
{
	return ApplyGameplayEffectSpecToSelf(*MakeSpec(EffectClass,1));
}


void UUTHUB_ASC::InitializeAttributesFromEffects()
{
	if (UGASDataComponent* DataComponent=GetOwner()->FindComponentByClass<UGASDataComponent>())
	{
		for (const auto& EffectClass : DataComponent->AttributeInitializers)
		{
		FGameplayEffectContextHandle EffectContext=MakeEffectContext();
			EffectContext.AddSourceObject(this);
			const FGameplayEffectSpecHandle spec=MakeOutgoingSpec(EffectClass,1,EffectContext);
			ApplyGameplayEffectSpecToSelf(*spec.Data.Get());
		}

	}
}







