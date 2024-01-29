// Mykola Shevchenko, All Rights Reserved

using UnrealBuildTool;
using System.Collections.Generic;

public class NL2CoasterImporterEditorTarget : TargetRules
{
	public NL2CoasterImporterEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "NL2CoasterImporter" } );
	}
}
