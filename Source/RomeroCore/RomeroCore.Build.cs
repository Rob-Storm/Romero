using UnrealBuildTool;

public class RomeroCore : ModuleRules
{
	public RomeroCore(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		bEnforceIWYU = true;	

		PublicDependencyModuleNames.AddRange(new string[] 
			{ 
				"Core", "CoreUObject", "Engine", "UMG", "AIModule", "InputCore", "EnhancedInput", "ChaosVehicles"
			});
		
		PrivateDependencyModuleNames.AddRange(new string[] { "OnlineSubsystem", "OnlineSubsystemUtils", "OnlineSubsystemNull", "Voice" });
	}
}