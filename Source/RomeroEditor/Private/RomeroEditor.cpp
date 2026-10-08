#include "RomeroEditor.h"
#include "Modules/ModuleManager.h"

#include "Logging/LogMacros.h"

DECLARE_LOG_CATEGORY_EXTERN(LogRomeroEditor, Log, All);
DEFINE_LOG_CATEGORY(LogRomeroEditor);

void FRomeroEditor::StartupModule()
{
	UE_LOG(LogRomeroEditor, Log, TEXT("RomeroEditor module starting up"));
}

void FRomeroEditor::ShutdownModule()
{
	UE_LOG(LogRomeroEditor, Log, TEXT("RomeroEditor module shutting down"));
}

IMPLEMENT_GAME_MODULE(FRomeroEditor, RomeroEditor);