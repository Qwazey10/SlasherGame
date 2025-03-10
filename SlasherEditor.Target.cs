// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SlasherEditorTarget : TargetRules
{
	public SlasherEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("Slasher");
	}
}