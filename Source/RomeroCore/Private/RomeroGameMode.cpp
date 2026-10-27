#include "RomeroGameMode.h"
#include "RomeroGameState.h"
#include "RomeroPlayerState.h"

#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"

#include "Serializable.h"
#include "Serialization/MemoryWriter.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"

#include "ChatMessage.h"

#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"

void ARomeroGameMode::InitGame(const FString &MapName, const FString &Options, FString &ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	ServerDeserialize();
}

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

void ARomeroGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{

	ARomeroPlayerState* PS = NewPlayer->GetPlayerState<ARomeroPlayerState>();
	if(ensure(PS))
	{
		PS->LoadPlayerState(CurrentSaveGame);
	}

	Super::HandleStartingNewPlayer_Implementation(NewPlayer);
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
	UE_LOG(LogTemp, Log, TEXT("Begin server serialize"));

	CurrentSaveGame->SavedActors.Empty();

	// Somehow replace iterator with these?
	//TArray<AActor*> SerializeableActors;
	//GetAllActorsWithInterface(this, USerializeable::StaticClass(), SerializeableActors);

	for(FActorIterator It(GetWorld()); It; ++It)
	{
		AActor* Actor = *It;

		if(Actor->IsPendingKillPending() || !Actor->Implements<USerializeable>())
		{
			continue;
		}

		FActorSaveData ActorData;

		ActorData.ActorID = Actor->GetActorGuid();
		ActorData.ActorName = Actor->GetFName();
		ActorData.ActorClass = Actor->GetClass();
		ActorData.Transform = Actor->GetActorTransform();

		FMemoryWriter MemWriter(ActorData.ByteData);

		FObjectAndNameAsStringProxyArchive Ar(MemWriter, true);
		Ar.ArIsSaveGame = true;

		Actor->Serialize(Ar);

		CurrentSaveGame->SavedActors.Add(ActorData);
	}

	UE_LOG(LogTemp, Log, TEXT("Serialized %i Actors"), CurrentSaveGame->SavedActors.Num());

	UGameplayStatics::SaveGameToSlot(CurrentSaveGame, GetServerSaveSlot(), 0);
}

void ARomeroGameMode::ServerDeserialize()
{
	UE_LOG(LogTemp, Log, TEXT("Begin server deserialize"));

	if (UGameplayStatics::DoesSaveGameExist(GetServerSaveSlot(), 0))
	{
		CurrentSaveGame = Cast<UServerSaveGame>(UGameplayStatics::LoadGameFromSlot(GetServerSaveSlot(), 0));
		if (CurrentSaveGame == nullptr)
		{
		  	UE_LOG(LogTemp, Warning, TEXT("Failed to load SaveGame Data."));
			return;
		}

		UE_LOG(LogTemp, Log, TEXT("Loaded SaveGame Data."));

		UE_LOG(LogTemp, Log, TEXT("Serialized Actors in SaveGame: %i"), CurrentSaveGame->SavedActors.Num());
	

		// Modify existing actors
		for (FActorIterator It(GetWorld()); It; ++It)
		{
			AActor* Actor = *It;

			if (!Actor->Implements<USerializeable>())
			{
			  	continue;
			}

			for(int32 i = 0; i < CurrentSaveGame->SavedActors.Num(); i++)
			{
				if (CurrentSaveGame->SavedActors[i].ActorID == Actor->GetActorGuid())
			  	{
			  		// the last parameter is very important for vehicles and other physics simulated actors!
					Actor->SetActorTransform(CurrentSaveGame->SavedActors[i].Transform, false, nullptr, ETeleportType::TeleportPhysics);

			  		SetupActor(Actor, CurrentSaveGame->SavedActors[i]);
			  		CurrentSaveGame->SavedActors.RemoveAt(i);

			  		break;
			  	}
			}
		}


		// spawn saved actors that don't exist in the level yet
		// anything still remaining in the SavedActors is fair game

		for (FActorSaveData ActorData : CurrentSaveGame->SavedActors)
		{
  			AActor* SpawnedActor = GetWorld()->SpawnActorDeferred<AActor>
  			(
  				ActorData.ActorClass, 
  				ActorData.Transform,
  				nullptr
  			);

			SetupActor(SpawnedActor, ActorData);

			SpawnedActor->FinishSpawning(ActorData.Transform);			
		}
	
		OnSaveGameLoaded.Broadcast(CurrentSaveGame);
	}
	else
	{
	  	CurrentSaveGame = Cast<UServerSaveGame>(UGameplayStatics::CreateSaveGameObject(UServerSaveGame::StaticClass()));
	
	  	UE_LOG(LogTemp, Log, TEXT("Created New SaveGame Data."));
	}

}


void ARomeroGameMode::SetupActor(AActor* Actor, FActorSaveData SaveData)
{
	FMemoryReader MemReader(SaveData.ByteData);

	FObjectAndNameAsStringProxyArchive Ar(MemReader, true);
	Ar.ArIsSaveGame = true;
	Actor->Serialize(Ar);

	ISerializeable::Execute_OnActorLoaded(Actor);
}
