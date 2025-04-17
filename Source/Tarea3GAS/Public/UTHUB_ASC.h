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
	void AddAbilityFromClass(const TSubclassOf<UGameplayAbility>& InAbilityClass,const uint8& InInputID);
	virtual void InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor) override;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	//void InitializeAttributes(const AActor* InOwnerActor) const;
	void InitializeAttributesFromEffects();



public:
	
	UFUNCTION(BlueprintCallable, Category="GameEffects",meta=(AllowPrivateAccess=true))
	FActiveGameplayEffectHandle ApplyEffectFromClassToTarget(const TSubclassOf<UGameplayEffect>& EffectClass);
	
	UFUNCTION(BlueprintCallable, Category="GameEffects",meta=(AllowPrivateAccess=true))
	FActiveGameplayEffectHandle ApplyEffectFromClassToSelf(const TSubclassOf<UGameplayEffect>& EffectClass);

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=GameplayTag,meta=(AllowPrivateAccess=true))
	FGameplayTag ClassTag;
	
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
