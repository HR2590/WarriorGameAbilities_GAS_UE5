// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "CoreAttributeSet.generated.h"



#define ATTRIBUTE_ACCESSORS(ClassName,PropertyName)\
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName,PropertyName)\
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)\
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName)\
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


USTRUCT(BlueprintType,Blueprintable)
struct FGameplayCoreAttribute:public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)FGameplayAttribute Attribute;
	UPROPERTY(EditAnywhere)float AttributeBaseValue;
	
};


UCLASS()
class TAREA3GAS_API UCoreAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	UCoreAttributeSet();
	
	UPROPERTY(BlueprintReadOnly,Category="Attributes|CommonSet") FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UCoreAttributeSet,Health);
	UPROPERTY(BlueprintReadOnly,Category="Attributes|CommonSet") FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UCoreAttributeSet,Damage);
	UPROPERTY(BlueprintReadOnly,Category="Attributes|CommonSet") FGameplayAttributeData Speed;
	ATTRIBUTE_ACCESSORS(UCoreAttributeSet,Speed);
	// Called every frame

};

