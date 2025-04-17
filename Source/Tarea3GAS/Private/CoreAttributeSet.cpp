// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreAttributeSet.h"
#include "GameplayEffectExtension.h"

UCoreAttributeSet::UCoreAttributeSet()
{
	TSubclassOf<UCoreAttributeSet> AttributeClass=StaticClass();
	TArray<FGameplayAttribute> Attributes;
	GetAttributesFromSetClass(AttributeClass,Attributes);
	for (auto InAttribute : Attributes)
	{
		FOnAttributeChanged PostDelegate;
		OnAttributeChanged.Add(InAttribute,PostDelegate);
	}
}

void UCoreAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetMaxHealthAttribute())
	{
		const float CurrentHealth = Health.GetCurrentValue();
		const float NewMax = MaxHealth.GetCurrentValue();
		Health.SetCurrentValue(FMath::Clamp(CurrentHealth, 0.0f, NewMax));
		
		MaxHealth.SetCurrentValue(NewMax);
		MaxHealth.SetBaseValue(NewMax);
		
		
	}
	
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		float OldHealth = Health.GetCurrentValue();
		float NewHealth = FMath::Clamp(OldHealth, 0.0f, MaxHealth.GetCurrentValue());
        
		Health.SetCurrentValue(NewHealth);
		Health.SetBaseValue(NewHealth);
	
		
	}


	
}


void UCoreAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute,float OldValue,float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
	if(OnAttributeChanged.IsEmpty()) return;
	for (auto [InAttribute,Delegate] : OnAttributeChanged)
	{
		if(InAttribute==Attribute&&Delegate.IsBound())
		{
			Delegate.Broadcast(OldValue,NewValue);
		}
	}
	
}



