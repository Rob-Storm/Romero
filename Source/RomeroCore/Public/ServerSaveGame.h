#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameFramework/SaveGame.h"

#include "ServerSaveGame.generated.h"

/** Data serialized by the server to maintain games across different sessions */

/* Ideas for saving/loading:
 *
 * 	Server save data (player built prefabs, vehicle locations, NOT zombies or ground items) will be updated every so often
 *
 *	Player save data (logged out position, stats, inventory items, etc.) will be a USaveGame stored on the server
 *
 * 	Get FUniqueNetIdRepl to differentiate players at the connection level (this does persist between joins!)
 *
 * 	Server creates a map between NetId and PlayerSaveGame
 *
 * 	Players logging in will try to get theirs and store in their player state, a no entry will use default spawning behaviour (no items, randomized APlayerStart location)
 */

UCLASS()
class UServerSaveGame : public USaveGame
{
	GENERATED_BODY()

public:


	
};
