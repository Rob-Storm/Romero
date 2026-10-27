#include "ServerSaveGame.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/OnlineReplStructs.h"

FPlayerSaveData* UServerSaveGame::GetPlayerData(APlayerState* PlayerState)
{
	if (PlayerState == nullptr)
	{
		return nullptr;
	}

#if WITH_EDITOR

	if (PlayerState->GetWorld()->IsPlayInEditor())
	{
		UE_LOG(LogTemp, Log, TEXT("During PIE we cannot use PlayerID to retrieve Saved Player data. Using first entry in array if available."));

		if (SavedPlayers.IsValidIndex(0))
		{
			UE_LOG(LogTemp, Warning, TEXT("Getting first element of SavedPlayers data"));
			return &SavedPlayers[0];
		}

		UE_LOG(LogTemp, Warning, TEXT("First element was not valid, the array may be empty"));

		// No saved player data available
		return nullptr;
	}

#endif

	FString PlayerID = PlayerState->GetUniqueId()->ToString();
	
	return SavedPlayers.FindByPredicate([&](const FPlayerSaveData& Data) { return Data.PlayerID == PlayerID; });
}