// Copyright Epic Games, Inc. All Rights Reserved.

#include "NoLimit2CoasterImporter.h"

#define LOCTEXT_NAMESPACE "FNoLimit2CoasterImporterModule"

void FNoLimit2CoasterImporterModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FNoLimit2CoasterImporterModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FNoLimit2CoasterImporterModule, NoLimit2CoasterImporter)