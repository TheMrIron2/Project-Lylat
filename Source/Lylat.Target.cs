// Copyright 2020 Project Lylat. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class LylatTarget : TargetRules
{
	public LylatTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange(new string[] { "Lylat" });
	}
}
