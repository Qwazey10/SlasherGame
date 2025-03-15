// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Slasher : ModuleRules
{
	public Slasher(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"HeadMountedDisplay",
			"ImGui",
			"Niagara",
			"Slate",
			"SlateCore",
			"PhysicsCore",
			"Water",
			"NavigationSystem"
		});
	}
}