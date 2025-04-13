// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EAbilityInputID.h"
#include "AbilityInputMap.h"
#include "Engine/DataAsset.h"
#include "InputAbilityMapping.generated.h"

/**
 * 
 */
UCLASS()
class TAREA3GAS_API UInputAbilityMapping : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,Category=InputID)
	TMap<EAbilityInputID,FAbilityInputMap> InputMap;
	
};
