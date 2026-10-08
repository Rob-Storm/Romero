using UnrealBuildTool;

public class RomeroEditorTarget : TargetRules
{
	public RomeroEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		ExtraModuleNames.AddRange( new string[] { "RomeroCore" } );
	}
}