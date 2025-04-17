#pragma once
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"

class FGameplayTagsManager:public  FNoncopyable
{
	static FGameplayTagsManager* Singleton;

	

public:
	//Lazy Load
	static FGameplayTagsManager& Get()
	{
		if (!Singleton)
		{
			Singleton = new FGameplayTagsManager();
			return *Singleton;
		}
		return *Singleton;
	}
	

	void InitGameplayTags()
	{
		//Abilities
		Attack=UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Abilities.Attack"));
		Celebrate=UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Abilities.Celebrate"));
		Dodge=UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Abilities.Dodge"));
		Guard=UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Abilities.Guard"));
		Jump=UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Abilities.Jump"));
		TargetEnemy=UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Abilities.TargetEnemy"));
		//States
		IsBlocking=UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("States.IsBlocking"));
		IsBusy=UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("States.IsBusy"));
		IsShielding=UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("States.IsShielding"));
		Infected=UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("States.Infected"));
		//GameplayCues
		Burning=UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GameplayCues.Burning"));
		SpeedingUp=UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GameplayCues.SpeedingUp"));
		SpikeDamage=UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GameplayCues.SpikeDamage"));
		Zombie=UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GameplayCues.Zombie"));
		//Characters
		Lava=UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Characters.Lava"));
		Player=UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Characters.Player"));
		Enemy=UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Characters.Enemy"));
		HealthPotion=UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Characters.HealthPotion"));
		
		
	}
	//Abilities
	FGameplayTag Attack;
	FGameplayTag Celebrate;
	FGameplayTag Dodge;
	FGameplayTag Guard;
	FGameplayTag Jump;
	FGameplayTag TargetEnemy;
	//States
	FGameplayTag IsBlocking;
	FGameplayTag IsBusy;
	FGameplayTag IsShielding;
	FGameplayTag Infected;
	//GameplayCues
	FGameplayTag Burning;
	FGameplayTag SpeedingUp;
	FGameplayTag SpikeDamage;
	FGameplayTag Zombie;
	//Actors
	FGameplayTag Lava;
	FGameplayTag Player;
	FGameplayTag Enemy;
	FGameplayTag HealthPotion;
	
};
