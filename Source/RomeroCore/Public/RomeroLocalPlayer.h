#pragma once

#include "CoreMinimal.h"
#include "Engine/LocalPlayer.h"

#include "RomeroLocalPlayer.generated.h"

UCLASS(Config=Engine)
class URomeroLocalPlayer : public ULocalPlayer
{
	GENERATED_BODY()

public:

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category="RomeroLocalPlayer")
	FString PlayerName = TEXT("ragamuffin");

	virtual FString GetNickname() const override
	{
		return PlayerName;
	}
	
};
