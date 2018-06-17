#pragma once
 #include "ModuleManager.h"


class FSkyPlugin : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	void StartupModule();
	void ShutdownModule();

	
};

