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

void UUTHUB_ASC::AddAbilityFromClass(const TSubclassOf<UGameplayAbility>& InAbilityClass,const uint8& InInputID)
{
	const FGameplayAbilitySpec Spec(InAbilityClass,1,InInputID,this);
	GiveAbility(Spec);
	
}


FActiveGameplayEffectHandle UUTHUB_ASC::ApplyEffectFromClassToTarget(const TSubclassOf<UGameplayEffect>& EffectClass)
{
	FGameplayEffectContextHandle EffectContext=MakeEffectContext();
	EffectContext.AddSourceObject(this);
	return ApplyGameplayEffectSpecToTarget(*MakeOutgoingSpec(EffectClass,1,EffectContext).Data.Get(),this);

}

FActiveGameplayEffectHandle UUTHUB_ASC::ApplyEffectFromClassToSelf(const TSubclassOf<UGameplayEffect>& EffectClass)
{
	FGameplayEffectContextHandle EffectContext=MakeEffectContext();
	EffectContext.AddSourceObject(this);
	return ApplyGameplayEffectSpecToSelf(*MakeOutgoingSpec(EffectClass,1,EffectContext).Data.Get());
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







