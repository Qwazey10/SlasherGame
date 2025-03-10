// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SlasherTarget : TargetRules
{
	public SlasherTarget(TargetInfo target) : base(target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("Slasher");
	}
}