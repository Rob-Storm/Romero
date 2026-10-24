#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"

#include "RomeroGameMode.generated.h"

UCLASS()
class ARomeroGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

private:

	UFUNCTION()
	void SendServerMessage(const FString &Message);
	
};