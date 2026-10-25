#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "RomeroGameInstance.generated.h"

UCLASS()
class URomeroGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Multiplayer")
	FString PlayerName = TEXT("ragamuffin");

};