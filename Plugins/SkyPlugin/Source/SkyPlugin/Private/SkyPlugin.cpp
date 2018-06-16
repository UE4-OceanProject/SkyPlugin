// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "SkyPlugin.h"
#include "Modules/ModuleManager.h"

void FSkyPlugin::StartupModule()
{
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)
}


void FSkyPlugin::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

IMPLEMENT_MODULE(FDefaultGameModuleImpl, SkyPlugin)

