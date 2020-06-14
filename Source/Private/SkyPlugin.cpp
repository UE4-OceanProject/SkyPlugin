// For copyright see LICENSE in EnvironmentProject root dir, or:
//https://github.com/UE4-OceanProject/OceanProject/blob/Master-Environment-Project/LICENSE

#include "SkyPlugin.h"
#include "EngineUtils.h"

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



ASkyManager* FSkyPlugin::SpawnSingletonActor(UWorld* World)
{
	FVector location = FVector(0, 0, 0);
	FRotator rotate = FRotator(0, 0, 0);
	FActorSpawnParameters SpawnInfo;
	return World->SpawnActor<ASkyManager>(ASkyManager::StaticClass(), location, rotate, SpawnInfo);
}


ASkyManager* FSkyPlugin::GetSingletonActor(UObject* WorldContextObject)
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

