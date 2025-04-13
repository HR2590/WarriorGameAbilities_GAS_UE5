// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreAttributeSet.h"

#include "GameplayEffectExtension.h"

UCoreAttributeSet::UCoreAttributeSet()
{
}

void UCoreAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		
		float OldHealth = Health.GetCurrentValue();
		float NewHealth = FMath::Clamp(OldHealth, 0.0f, 100.0f);
        
		Health.SetCurrentValue(NewHealth);
		Health.SetBaseValue(NewHealth);

		// Disparar el delegate si hay algún cambio en la vida
		OnHealthChanged.Broadcast(OldHealth, NewHealth);
	}
	if (Data.EvaluatedData.Attribute == GetSpeedAttribute())
	{
		
		// Disparar el delegate si hay algún cambio en la vida
		OnSpeedChanged.Broadcast(Speed.GetCurrentValue(), Speed.GetBaseValue());
	
	}
}

