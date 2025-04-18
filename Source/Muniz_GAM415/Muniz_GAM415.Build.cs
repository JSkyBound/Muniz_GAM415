// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Muniz_GAM415 : ModuleRules
{
	public Muniz_GAM415(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] { "Paper2D" });
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "Niagara", "ProceduralMeshComponent" });
	}
}
