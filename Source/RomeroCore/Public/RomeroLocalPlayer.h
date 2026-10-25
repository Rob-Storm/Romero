#pragma once

#include "CoreMinimal.h"
#include "Engine/LocalPlayer.h"

#include "RomeroLocalPlayer.generated.h"

UCLASS(Config="GameUserSettings")
class URomeroLocalPlayer : public ULocalPlayer
{
	GENERATED_BODY()

public:

	UPROPERTY(Config, EditAnywhere, BlueprintReadonly, Category="RomeroLocalPlayer")
	FString PlayerName = TEXT("ragamuffin");

	virtual FString GetNickname() const override
	{
		return PlayerName;
	}

	UFUNCTION(BlueprintCallable, Category="RomeroLocalPlayer")
	void SetPlayerName(const FString &NewName)
	{
		PlayerName = NewName;

		SaveConfig();
	}
	
};
