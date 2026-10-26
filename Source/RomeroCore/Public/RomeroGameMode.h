#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"

#include "ServerSaveGame.h"

#include "RomeroGameMode.generated.h"

UCLASS()
class ARomeroGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TObjectPtr<UServerSaveGame> CurrentSaveGame;

	UFUNCTION(BlueprintPure, Category="Serialization")
	static FString GetServerSaveSlot()
	{
		return TEXT("ServerSaveSlot");
	}

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

private:

	UFUNCTION()
	void ServerSerialize();

	UFUNCTION()
	void ServerDeserialize();

	// UFUNCTION()
	// void ClientTryGetSave();

	UFUNCTION()
	void SendServerMessage(const FString &Message);
	
};