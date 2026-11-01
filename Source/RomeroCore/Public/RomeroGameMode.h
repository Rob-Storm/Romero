#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"

#include "ServerSaveGame.h"

#include "RomeroGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSaveGameLoadedSignature, UServerSaveGame*, SaveGame);

UCLASS()
class ARomeroGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Serialization")
	FOnSaveGameLoadedSignature OnSaveGameLoaded;

	UPROPERTY()
	TObjectPtr<UServerSaveGame> CurrentSaveGame;

	UFUNCTION(BlueprintPure, Category="Serialization")
	static FString GetServerSaveSlot()
	{
		return TEXT("ServerSaveSlot");
	}

	UFUNCTION(BlueprintCallable, Category="Serialization")
	void RequestSave()
	{
		ServerSerialize();
	}

	UFUNCTION(BlueprintCallable, Category="Multiplayer")
	void AnnouncePlayerDead(APlayerState* DeadPlayer);

	virtual void InitGame(const FString &MapName, const FString &Options, FString &ErrorMessage) override;

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void RestartPlayer(AController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

private:

	UPROPERTY()
	FString SlotName;

	UPROPERTY()
	FTimerHandle RespawnHandle;

	UFUNCTION()
	void ServerSerialize();

	UFUNCTION()
	void ServerDeserialize();

	UFUNCTION()
	void SetupActor(AActor* Actor, FActorSaveData SaveData);

	// UFUNCTION()
	// void ClientTryGetSave();

	UFUNCTION()
	void SendServerMessage(const FString &Message);
	
};