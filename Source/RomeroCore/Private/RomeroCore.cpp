#include "RomeroCore.h"
#include "Modules/ModuleManager.h"

#include "Logging/LogMacros.h"

DECLARE_LOG_CATEGORY_EXTERN(LogRomeroCore, Log, All);
DEFINE_LOG_CATEGORY(LogRomeroCore);

void FRomeroCore::StartupModule()
{
	UE_LOG(LogRomeroCore, Log, TEXT("RomeroCore module starting up"));
}

void FRomeroCore::ShutdownModule()
{
	UE_LOG(LogRomeroCore, Log, TEXT("RomeroCore module shutting down"));
}

IMPLEMENT_PRIMARY_GAME_MODULE(FDefaultGameModuleImpl, RomeroCore, "RomeroCore");