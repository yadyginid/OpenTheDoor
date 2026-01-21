// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class OpenTheDoor : ModuleRules
{
	public OpenTheDoor(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] { "AIModule" });
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput",  "GameplayAbilities", "GameplayTags", "GameplayTasks" });
	}
}
