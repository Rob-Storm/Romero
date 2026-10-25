#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RomeroLocalPlayer.h"

#include "RomeroGameInstance.generated.h"

UCLASS()
class URomeroGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category="Multiplayer")
	void SetPlayerName(const FString &NewName)
	{
		URomeroLocalPlayer* LocalPlayer = Cast<URomeroLocalPlayer>(GetFirstGamePlayer());

		if(!LocalPlayer)
		{
			return;
		}

		LocalPlayer->PlayerName = NewName;
	}

};