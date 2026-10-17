#include "RomeroGameState.h"
#include "Net/UnrealNetwork.h"


ARomeroGameState::ARomeroGameState()
{
	bReplicateUsingRegisteredSubObjectList = true;
}

void ARomeroGameState::Server_SendChatMessage_Implementation(const FChatMessage& Message)
{

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Message received"));

	ChatHistory.Add(Message);

	OnRep_ChatHistory();
}

void ARomeroGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARomeroGameState, ChatHistory);
}


void ARomeroGameState::OnRep_ChatHistory()
{
	OnChatHistoryChanged.Broadcast();
}