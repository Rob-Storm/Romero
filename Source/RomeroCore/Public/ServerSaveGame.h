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
	FName ActorName;

	UPROPERTY()
	FTransform Transform;

	UPROPERTY()
	TArray<uint8> ByteData;
}


USTRUCT()
struct FPlayerSaveData
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FString PlayerId;

	UPROPERTY()
	FVector Location;

	UPROPERTY()
	FRotator Rotation;
	
	UPROPERTY()
	bool IsAlive;
};

UCLASS()
class UServerSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Serialization")
	TArray<FPlayerSaveData> SavedPlayers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Serialization")
	TArray<AActor*> SavedActors;

	
};
