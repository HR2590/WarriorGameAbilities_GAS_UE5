// Copyright Epic Games, Inc. All Rights Reserved.

#include "Tarea3GAS.h"
#include "FGameplayTagsManager.h"
#include "GameplayTagsManager.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_PRIMARY_GAME_MODULE(ITagManager, Tarea3GAS, "Tarea3GAS" );

DEFINE_LOG_CATEGORY(LogTarea3GAS)


void ITagManager::StartupModule()
{
	IModuleInterface::StartupModule();
	UGameplayTagsManager::OnLastChanceToAddNativeTags().AddLambda([]()
	{
		FGameplayTagsManager::Get().InitGameplayTags();
	
	});
}

void ITagManager::ShutdownModule()
{
	IModuleInterface::ShutdownModule();
}
