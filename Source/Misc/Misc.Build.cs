// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Misc : ModuleRules
{
	public Misc(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.Add(ModuleDirectory);


		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core",
			"CoreUObject",
			"Engine", 
			"InputCore" ,
			"ProceduralMeshComponent" ,
			"AIModule"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
