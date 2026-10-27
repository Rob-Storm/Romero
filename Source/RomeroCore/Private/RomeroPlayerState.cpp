#include "RomeroPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "RomeroGameInstance.h"

#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

#include "GameFramework/OnlineReplStructs.h"

void ARomeroPlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}


void ARomeroPlayerState::SavePlayerState_Implementation(UServerSaveGame* SaveObject)
{
    if (!SaveObject)
    {
        return;
    }

    FPlayerSaveData SaveData;

    if (!GetUniqueId().IsValid())
    {
        UE_LOG(LogTemp, Warning, TEXT("Cannot save player: unique ID is invalid."));
        return;
    }

	SaveData.LastTransform = LastSpawnTransform;
	SaveData.IsAlive = true;

    SaveData.PlayerID = GetUniqueId()->ToString();


    FPlayerSaveData* ExistingData = SaveObject->SavedPlayers.FindByPredicate
	(
		[&SaveData](const FPlayerSaveData& Data){ return Data.PlayerID == SaveData.PlayerID;}
	);

    if (ExistingData)
    {
        *ExistingData = SaveData;
    }
    else
    {
        SaveObject->SavedPlayers.Add(SaveData);
    }

    UE_LOG(LogTemp, Log, TEXT("Saved player data for ID %s"), *SaveData.PlayerID);
}


void ARomeroPlayerState::LoadPlayerState_Implementation(UServerSaveGame* SaveObject)
{
	if(!SaveObject)
	{
		return;
	}

	FPlayerSaveData* FoundData = SaveObject->GetPlayerData(this);
	if(FoundData)
	{
		UE_LOG(LogTemp, Warning, TEXT("Successfully loaded SaveGame data for player id %s"), *GetUniqueId()->ToString())

		UE_LOG(LogTemp, Warning, TEXT("%s"), *FoundData->LastTransform.ToString());

		LastSpawnTransform = FoundData->LastTransform;

		QuitDead = !FoundData->IsAlive;

		UE_LOG(LogTemp, Warning, TEXT("QuitDead %s"), QuitDead ? TEXT("TRUE") : TEXT("FALSE"));

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not find SaveGame data for player id %s"), *GetUniqueId()->ToString())
	}

}