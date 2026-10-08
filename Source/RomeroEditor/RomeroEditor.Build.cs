using UnrealBuildTool;

public class RomeroEditor : ModuleRules
{
	public RomeroEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		bEnforceIWYU = true;	

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "RomeroCore" });
		PrivateDependencyModuleNames.AddRange(new string[] { });
	}
}