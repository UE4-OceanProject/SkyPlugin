/*=================================================
* For parts referencing UE4 code, the following copyright applies:
* Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
*
* Feel free to use this software in any commercial/free game.
* Selling this as a plugin/item, in whole or part, is not allowed.
* See LICENSE for full licensing details.
* =================================================*/

#include "SkyPlugin.h"
#include "EngineUtils.h"
#include "Editor/EditorEngine.h"

DEFINE_LOG_CATEGORY(SkyPlugin);

void FSkyPlugin::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FSkyPlugin::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}



ASkyManager * FSkyPlugin::SpawnSingletonActor(UWorld * World)
{
	FVector location = FVector(0, 0, 0);
	FRotator rotate = FRotator(0, 0, 0);
	FActorSpawnParameters SpawnInfo;
	return World->SpawnActor<ASkyManager>(ASkyManager::StaticClass(), location, rotate, SpawnInfo);
}


ASkyManager * FSkyPlugin::GetSingletonActor(UObject* WorldContextObject)
{
	UWorld* World = WorldContextObject->GetWorld();

	//Find the sky manager if there is one spawned 
	for (TActorIterator<ASkyManager> ActorItr(World); ActorItr; ++ActorItr)
	{
		return *ActorItr;
	}

	//If there isn't a sky manager in the world return null!
	return NULL;
}

IMPLEMENT_MODULE(FSkyPlugin, SkyPlugin)

