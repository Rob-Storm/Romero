#include "RomeroPlayerState.h"
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
	if(!SaveObject)
	{
		return;
	}

	FPlayerSaveData SaveData;

	SaveData.PlayerID = GetUniqueId()->ToString();

	// if false, player is currently dead
	if(APawn* MyPawn = GetPawn())
	{
		SaveData.Location = MyPawn->GetActorLocation();
		SaveData.Rotation = MyPawn->GetActorRotation();
		SaveData.IsAlive = true;
	}

	UE_LOG(LogTemp, Warning, TEXT("Saving player data with id %s"), *SaveData.PlayerID);

	SaveObject->SavedPlayers.Add(SaveData);
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
		FTransform spawnTransform(FoundData->Rotation, FoundData->Location, FVector::OneVector);

		LastSpawnTransform = spawnTransform;
		QuitDead = !FoundData->IsAlive;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not find SaveGame data for player id %s"), *GetUniqueId()->ToString())
	}

}