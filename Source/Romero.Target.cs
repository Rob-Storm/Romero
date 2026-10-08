using UnrealBuildTool;

public class RomeroTarget : TargetRules
{
	public RomeroTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		ExtraModuleNames.AddRange( new string[] { "RomeroCore" } );
	}
}