// Copyright 2020 Team Project Lylat. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class LylatEditorTarget : TargetRules
{
	public LylatEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange(new string[] { "Lylat" });
	}
}
