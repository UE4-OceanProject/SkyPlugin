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

DEFINE_LOG_CATEGORY(SkyPlugin);

void FSkyPlugin::StartupModule()
{
	UE_LOG(SkyPlugin, Warning, TEXT("TimePlugin StartupModle() Register OnWorldCreated delegate"));

	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	//Create our delegate type
	FWorldDelegates::FWorldInitializationEvent::FDelegate OnWorldCreatedDelegate;
	//Declare which function we want to bind to
	OnWorldCreatedDelegate = FWorldDelegates::FWorldInitializationEvent::FDelegate::CreateRaw(this, &FSkyPlugin::OnWorldCreated);
	//Declare which event we want to bind to
	FDelegateHandle OnWorldCreatedDelegateHandle = FWorldDelegates::OnPostWorldInitialization.Add(OnWorldCreatedDelegate);
}


void FSkyPlugin::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

void FSkyPlugin::OnWorldCreated(UWorld* World, const UWorld::InitializationValues IVS)
{
	//If we already have a SkyManagerActor do not spawn another one
	//Just store it as the current SkyManagerActor for other plugins to use
	//Only pick the first instance

	for (TActorIterator<ASkyManager> ActorItr(World); ActorItr; ++ActorItr)
	{
		SkyManagerActor = *ActorItr;
		return;
	}
	FVector location = FVector(0, 0, 0);
	FRotator rotate = FRotator(0, 0, 0);
	FActorSpawnParameters SpawnInfo;
	SkyManagerActor = World->SpawnActor<ASkyManager>(ASkyManager::StaticClass(), location, rotate, SpawnInfo);
}


IMPLEMENT_MODULE(FSkyPlugin, SkyPlugin)

