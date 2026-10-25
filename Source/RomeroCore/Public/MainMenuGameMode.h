#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"

#include "MainMenuGameMode.generated.h"

UCLASS()
class AMainMenuGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent, Category="RomeroCore")
	void PreMapTransition();

	virtual void StartToLeaveMap() override
	{
		Super::StartToLeaveMap();
		PreMapTransition();
	}
	
};
