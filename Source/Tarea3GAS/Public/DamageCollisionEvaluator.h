// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "DamageCollisionEvaluator.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TAREA3GAS_API UDamageCollisionEvaluator : public UBoxComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDamageCollisionEvaluator();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
};
