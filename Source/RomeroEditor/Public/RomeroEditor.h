#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

class FRomeroEditor : public IModuleInterface
{
public:
	static inline FRomeroEditor& Get()
	{
		return FModuleManager::LoadModuleChecked<FRomeroEditor>("RomeroEditor");
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("RomeroEditor");
	}

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};