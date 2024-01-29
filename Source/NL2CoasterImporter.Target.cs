// Mykola Shevchenko, All Rights Reserved

using UnrealBuildTool;
using System.Collections.Generic;

public class NL2CoasterImporterTarget : TargetRules
{
	public NL2CoasterImporterTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "NL2CoasterImporter" } );
	}
}
