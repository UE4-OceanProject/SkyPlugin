// For copyright see LICENSE in EnvironmentProject root dir, or:
//https://github.com/UE4-OceanProject/OceanProject/blob/Master-Environment-Project/LICENSE

#include "SkyPlugin.h"
#include "EngineUtils.h"

DEFINE_LOG_CATEGORY(LogSkyPlugin);

void FSkyPlugin::StartupModule()
{
	UE_LOG(LogSkyPlugin, Log, TEXT("%s:: Module started"), *PLUGIN_FUNC_LINE);
}

void FSkyPlugin::ShutdownModule()
{
}

ASkyManager* FSkyPlugin::SpawnSingletonActor(UWorld* World)
{
	FActorSpawnParameters SpawnInfo;
	ASkyManager* TimeManager = World->SpawnActor<ASkyManager>(ASkyManager::StaticClass(), FTransform::Identity, FActorSpawnParameters());
	if (!TimeManager)
		UE_LOG(LogSkyPlugin, Warning, TEXT("%s:: Failed to spawn Singleton!"), *PLUGIN_FUNC_LINE);

	return TimeManager;
}


ASkyManager* FSkyPlugin::GetSingletonActor(UObject* WorldContextObject)
{
	UWorld* World = WorldContextObject->GetWorld();
	
	if ((World->WorldType == EWorldType::EditorPreview) || (World->WorldType == EWorldType::GamePreview))
		return NULL;
	if (World->bIsRunningConstructionScript)
		return NULL;

	//Find the sky manager if there is one spawned 
	for (TActorIterator<ASkyManager> ActorItr(World); ActorItr; ++ActorItr)
	{
		return *ActorItr;
	}

	//If there isn't a sky manager in the world return null!
	UE_LOG(LogSkyPlugin, Display, TEXT("%s:: No SkyManager found... spawning..."), *PLUGIN_FUNC_LINE);
	return NULL;
}

IMPLEMENT_MODULE(FSkyPlugin, SkyPlugin)

