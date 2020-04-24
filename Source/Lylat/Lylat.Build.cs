// Copyright 2020 Project Lylat. All Rights Reserved.

using UnrealBuildTool;

public class Lylat : ModuleRules
{
	public Lylat(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG" });
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
	}
}
