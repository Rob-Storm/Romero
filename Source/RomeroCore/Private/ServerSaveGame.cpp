#include "ServerSaveGame.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/OnlineReplStructs.h"

FPlayerSaveData* UServerSaveGame::GetPlayerData(APlayerState* PlayerState)
{
	if (PlayerState == nullptr)
	{
		return nullptr;
	}

	if (PlayerState->GetWorld()->IsPlayInEditor())
	{
		UE_LOG(LogTemp, Log, TEXT("During PIE we cannot use PlayerID to retrieve Saved Player data. Using first entry in array if available."));

		if (SavedPlayers.IsValidIndex(0))
		{
			return &SavedPlayers[0];
		}

		// No saved player data available
		return nullptr;
	}


	FString PlayerID = PlayerState->GetUniqueId()->ToString();

	return SavedPlayers.FindByPredicate([&](const FPlayerSaveData& Data) { return Data.PlayerID == PlayerID; });
}