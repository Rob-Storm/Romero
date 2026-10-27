#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"

#include "ServerSaveGame.h"

#include "RomeroPlayerState.generated.h"

UCLASS()
class ARomeroPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FTransform LastSpawnTransform;

	UPROPERTY()
	bool QuitDead = true;

	UFUNCTION(BlueprintNativeEvent)
	void SavePlayerState(UServerSaveGame* SaveObject);

	UFUNCTION(BlueprintNativeEvent)
	void LoadPlayerState(UServerSaveGame* SaveObject);

	virtual void PostInitializeComponents() override;
	
};
