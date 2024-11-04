// Copyright Lede Studios. All Rights Reserved.

using UnrealBuildTool;

public class ProjectDelta : ModuleRules
{
	public ProjectDelta(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.Add("ProjectDelta/");
        
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
