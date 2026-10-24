#include "RomeroAIController.h"
#include "UObject/Object.h"
#include "Net/UnrealNetwork.h"

ARomeroAIController::ARomeroAIController()
{
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>("PawnSense");
}

void ARomeroAIController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARomeroAIController, Target);
}
