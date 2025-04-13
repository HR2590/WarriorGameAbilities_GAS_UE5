// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "UTHUB_ASC.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TAREA3GAS_API UUTHUB_ASC : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UUTHUB_ASC();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	//void InitializeAttributes(const AActor* InOwnerActor) const;
	void InitializeAttributesFromEffects();

	virtual void InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor) override;
	FGameplayEffectSpec* MakeSpec(const TSubclassOf<UGameplayEffect>& EffectClass,int InLevel) const;

	UPROPERTY(EditAnywhere,Category=GameEffects,meta=(AllowPrivateAccess)) FGameplayTag TagClass;


public:
	
	UFUNCTION(BlueprintCallable, Category="GameEffects",meta=(AllowPrivateAccess=true))
	FActiveGameplayEffectHandle ApplyEffectFromClassToTarget(const TSubclassOf<UGameplayEffect>& EffectClass);
	
	UFUNCTION(BlueprintCallable, Category="GameEffects",meta=(AllowPrivateAccess=true))
	FActiveGameplayEffectHandle ApplyEffectFromClassToSelf(const TSubclassOf<UGameplayEffect>& EffectClass);
	

	template <typename AttrSetType>
	AttrSetType* GetAttributeSetFromOwner() const;
	
};

template <typename AttrSetType>
AttrSetType* UUTHUB_ASC::GetAttributeSetFromOwner() const
{
	if (!GetOwner()) return nullptr;
	TArray<UObject*> SubObjects;
	GetOwner()->GetDefaultSubobjects(SubObjects);
	UObject** AttSet=SubObjects.FindByPredicate([](const UObject* Object)
	{
		return Object->IsA(AttrSetType::StaticClass());
	});

	if (!AttSet) return nullptr;

	return Cast<AttrSetType>(*AttSet);
	
}
