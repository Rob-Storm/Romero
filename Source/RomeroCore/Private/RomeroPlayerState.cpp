#include "RomeroPlayerState.h"
#include "RomeroGameInstance.h"
#include "Kismet/GameplayStatics.h"

void ARomeroPlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	TObjectPtr<URomeroGameInstance> GI = Cast<URomeroGameInstance>(UGameplayStatics::GetGameInstance(this));

	if(GI)
	{
		SetPlayerName(GI->PlayerName);
	}
	else
	{
		SetPlayerName("ragamuffin");
	}

}