// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreAttributeSet.h"
#include "Components/ActorComponent.h"
#include "GASDataComponent.generated.h"


class UGameplayAttributeEffector;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TAREA3GAS_API UGASDataComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGASDataComponent();
	
	UPROPERTY(EditAnywhere,Category="Data",meta=(AllowPrivateAccess=true))
	TArray<TSubclassOf<class UGameplayEffect>> AttributeInitializers;
	
	UPROPERTY(EditAnywhere,Category="Data",meta=(AllowPrivateAccess=true))
	TMap<FGameplayAttribute,TSubclassOf<UGameplayEffect>> AttributeEffectors;
};
