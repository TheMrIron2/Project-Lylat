// Copyright (c) 2020 Team Project: Lylat. All Rights Reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish or distribute. This does not allow commercial distribution.
//
// This license does not cover any content made by any commercial entity.
//
// Under the category "content used without permission" falls any content regarding the "Star Fox" trademark.
// Star Fox is a registered trademark of Nintendo Co., Ltd.
// 
// Under the category "content used according to licensing" fall the Discord Game SDK and the Ultralight SDK.
// Discord is a registered trademark of Discord, Inc.
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

using System;
using System.IO;
using UnrealBuildTool;

public class Lylat : ModuleRules
{
	public Lylat(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Slate",
			"SlateCore"
		});

		string dllSuffix = ".", libSuffix = ".";
		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			dllSuffix			+= "dll";
			libSuffix			+= "dll.lib";
		}
		else if (Target.Platform == UnrealTargetPlatform.Mac)
		{
			dllSuffix			+= "dylib";
			libSuffix			+= "dylib";
		}
		else if (Target.Platform == UnrealTargetPlatform.Linux)
		{
			dllSuffix			+= "so";
			libSuffix			+= "so";
		}
		else throw new Exception("Unsupported platform.");

		PublicIncludePaths.AddRange(new string[]
		{
			Path.Combine(ModuleDirectory, "Discord")
		});

		PublicAdditionalLibraries.AddRange(new string[]
		{
			Path.Combine(ModuleDirectory, "Discord", "discord_game_sdk" + libSuffix)
		});

		PublicDelayLoadDLLs.AddRange(new string[]
		{
			Path.Combine(ModuleDirectory, "Discord", "discord_game_sdk" + dllSuffix)
		});

		RuntimeDependencies.Add("$(TargetOutputDir)/discord_game_sdk" + dllSuffix, Path.Combine(ModuleDirectory, "Discord", "discord_game_sdk" + dllSuffix));
	}
}
