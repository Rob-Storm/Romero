#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

class FRomeroCore : public IModuleInterface
{
public:
	static inline FRomeroCore& Get()
	{
		return FModuleManager::LoadModuleChecked<FRomeroCore>("RomeroCore");
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("RomeroCore");
	}

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};