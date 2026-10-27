#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameFramework/SaveGame.h"

#include "ServerSaveGame.generated.h"


USTRUCT()
struct FActorSaveData
{

	GENERATED_BODY()

public:

	UPROPERTY()
	FGuid ActorID;

	UPROPERTY()
	FName ActorName;

	UPROPERTY()
	TSubclassOf<AActor> ActorClass;

	UPROPERTY()
	FTransform Transform;

	UPROPERTY()
	TArray<uint8> ByteData;
};


USTRUCT()
struct FPlayerSaveData
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FString PlayerID;

	UPROPERTY()
	FTransform LastTransform;
	
	UPROPERTY()
	bool IsAlive;
};

UCLASS()
class UServerSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TArray<FPlayerSaveData> SavedPlayers;

	UPROPERTY()
	TArray<FActorSaveData> SavedActors;

	FPlayerSaveData* GetPlayerData(APlayerState* PlayerState);
	
};
