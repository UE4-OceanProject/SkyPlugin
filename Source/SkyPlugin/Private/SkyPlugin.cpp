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
	UE_LOG(SkyPlugin, Warning, TEXT("SkyPlugin StartupModle() Register OnWorldCreated delegate"));

	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	//Auto create our SkyManager
	//This is called everySky UWorld is created, which is a lot in the editor (every opened BP gets a UWorld)
	FWorldDelegates::OnPostWorldInitialization.AddRaw(this, &FSkyPlugin::InitSingletonActor);
}

void FSkyPlugin::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FWorldDelegates::OnPostWorldInitialization.RemoveAll(this);
}

void FSkyPlugin::EnforceSingletonActor(UWorld * World)
{
	//Make sure there is only one instance of this actor!
	//Actor is not blueprintable, but users will find other ways!!
	bool bFoundFirstInstance = false;
	for (TActorIterator<ASkyManager> ActorItr(World); ActorItr; ++ActorItr)
	{
		if (bFoundFirstInstance == false)
		{
			bFoundFirstInstance = true;
		}
		else
		{
			ActorItr->Destroy();
		}
	}
}

ASkyManager * FSkyPlugin::SpawnSingletonActor(UWorld * World)
{
	FVector location = FVector(0, 0, 0);
	FRotator rotate = FRotator(0, 0, 0);
	FActorSpawnParameters SpawnInfo;
	return World->SpawnActor<ASkyManager>(ASkyManager::StaticClass(), location, rotate, SpawnInfo);
}

void FSkyPlugin::InitSingletonActor(UWorld * World, const UWorld::InitializationValues IVS)
{
	//Make sure we are in the correct UWorld!
	if (World->WorldType == EWorldType::Game || EWorldType::PIE || EWorldType::GamePreview || EWorldType::GameRPC || EWorldType::Editor)
	{
		//If we already have a SkyManagerEditorActor in the editor level, do not spawn another one
		//This also auto spawns a SkyManagerActor in the game world, if the user somehow sneaks a map in
		//that has not been opened while the plugin was active!

		EnforceSingletonActor(World);

		for (TActorIterator<ASkyManager> ActorItr(World); ActorItr; ++ActorItr)
		{
			//If SkyManager already exists
			return;
		}

		//Spawn SkyManager since there isn't one already
		SpawnSingletonActor(World);
	}
}

ASkyManager * FSkyPlugin::GetSingletonActor(UObject* WorldContextObject)
{
	UWorld* World = WorldContextObject->GetWorld();

	EnforceSingletonActor(World);

	for (TActorIterator<ASkyManager> ActorItr(World); ActorItr; ++ActorItr)
	{
		return *ActorItr;
	}

	//In the impossible case that we don't have an actor, spawn one!
	return SpawnSingletonActor(World);
}

IMPLEMENT_MODULE(FSkyPlugin, SkyPlugin)

