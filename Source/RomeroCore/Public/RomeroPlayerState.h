#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"

#include "RomeroPlayerState.generated.h"

UCLASS()
class ARomeroPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent)
	void SavePlayerState(class UServerSaveGame* SaveObject);

	UFUNCTION(BlueprintNativeEvent)
	void LoadPlayerState(class UServerSaveGame* SaveObject);

	virtual void PostInitializeComponents() override;
	
};
