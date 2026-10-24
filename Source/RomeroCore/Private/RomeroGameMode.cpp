#include "RomeroGameMode.h"
#include "RomeroGameState.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"

#include "ChatMessage.h"

#include "Kismet/GameplayStatics.h"

void ARomeroGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if(TObjectPtr<APlayerState> PS = NewPlayer->GetPlayerState<APlayerState>())
	{
		SendServerMessage(PS->GetPlayerName() + TEXT(" has joined"));
	}
}

void ARomeroGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	if(TObjectPtr<APlayerController> PC = Cast<APlayerController>(Exiting))
	{
		if(TObjectPtr<APlayerState> PS = PC->GetPlayerState<APlayerState>())
		{
			SendServerMessage(PS->GetPlayerName() + TEXT(" has left"));
		}
	}
}


void ARomeroGameMode::SendServerMessage(const FString &Message)
{
	TObjectPtr<ARomeroGameState> GS = Cast<ARomeroGameState>(UGameplayStatics::GetGameState(this));

	if(!GS)
	{
		return;
	}

	FChatMessage serverMessage = FChatMessage();
	serverMessage.SenderName = TEXT("Server");
	serverMessage.Message = Message;


	GS->Server_SendChatMessage(serverMessage);
}