// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Tarea3GAS : ModuleRules
{
	public Tarea3GAS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput","GameplayAbilities","GameplayTasks" ,"GameplayTags"});
    }
}
