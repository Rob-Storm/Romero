#include "RomeroGameMode.h"
#include "RomeroGameState.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"

#include "Serializeable.h"
#include "Serialization/MemoryWriter.h"

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

	// trying to create UI while the world
	// is being 'torn down' will cause a crash
	if(Exiting == UGameplayStatics::GetPlayerController(this, 0))
	{
		return;
	}

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

void ARomeroGameMode::ServerSerialize()
{

	CurrentSaveGame->SavedActors.Empty();

	//TArray<AActor*> SerializeableActors;
	//GetAllActorsWithInterface(this, USerializeable::StaticClass(), SerializeableActors);

	for(FActorIterator It(GetWorld()); It; ++It)
	{
		AActor* Actor = *It;

		if(Actor->IsPendingKill() || !Actor->Implements<USerializeable>())
		{
			continue;
		}

		FActorSaveData ActorData;
		ActorData.ActorName = Actor->GetFName();
		ActorData.Transform = Actor->GetActorTransform();

		FMemoryWriter MemWriter(ActorData.ByteData);

		FObjectAndNameAsStringProxyArchive Ar(MemWriter, true);
		Ar.ArIsSaveGame = true;

		Actor->Serialize(Ar);

		CurrentSaveGame->SavedActors.Add(ActorData);
	}

	UGameplayStatics::SaveGameToSlot(CurrentSaveGame, GetServerSaveSlot(), 0);
}