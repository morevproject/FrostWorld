// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FrostWorld : ModuleRules
{
	public FrostWorld(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
