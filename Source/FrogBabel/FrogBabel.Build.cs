// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FrogBabel : ModuleRules
{
	public FrogBabel(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
