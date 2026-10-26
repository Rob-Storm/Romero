#include "RomeroVehicle.h"
#include "UObject/Object.h"
#include "Net/UnrealNetwork.h"

#include "GameFramework/Controller.h"
#include "GameFramework/PlayerState.h"

#include "Components/CapsuleComponent.h"

ARomeroVehicle::ARomeroVehicle()
{
	bReplicates = true;

	PlayerNameText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("PlayerName"));

	PlayerNameText->SetupAttachment(RootComponent);
}

void ARomeroVehicle::Server_EnterVehicle_Implementation(ARomeroPlayer* Player)
{
    UE_LOG(LogTemp, Warning, TEXT("Attempting vehicle enter"));

    // is vehicle already controlled by someone else?
    if(GetController())
    {
        UE_LOG(LogTemp, Error, TEXT("Vehicle already has an owner"));
        return;
    }

	OwningPlayerPawn = Player;

    TObjectPtr<ARomeroPlayerController> PC = Cast<ARomeroPlayerController>(OwningPlayerPawn->GetController());

    if(!PC)
    {
        OnRep_OwningPlayerPawn();
        return;
    }

    // stop controlling their human character
    // and switch to the vehicle
    PC->UnPossess();
    PC->Possess(this);

    PC->EnterCar();

    OnRep_OwningPlayerPawn();

    // attach old player pawn to vehicle

    FAttachmentTransformRules AttachRules = FAttachmentTransformRules(EAttachmentRule::KeepWorld, true);
    OwningPlayerPawn->AttachToActor(this, AttachRules);

    OwningPlayerPawn->SetActorEnableCollision(false);
    OwningPlayerPawn->SetActorHiddenInGame(true);

    UE_LOG(LogTemp, Warning, TEXT("Player entered vehicle"));

    OnPlayerEnterVehicle.Broadcast(PC);
}

void ARomeroVehicle::Server_ExitVehicle_Implementation()
{
    UE_LOG(LogTemp, Warning, TEXT("Attempting vehicle exit"));

    TObjectPtr<ARomeroPlayerController> PC = Cast<ARomeroPlayerController>(GetController());

    if(!PC)
    {
        return;
    }

    // stop controlling the vehicle 
    // and switch to their human character
    PC->UnPossess();
    PC->Possess(OwningPlayerPawn);

    PC->ExitCar();

    // detach old player pawn from vehicle
    OwningPlayerPawn->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
    OwningPlayerPawn->SetActorEnableCollision(true);
    OwningPlayerPawn->SetActorHiddenInGame(false);

    OwningPlayerPawn = nullptr;
    OnRep_OwningPlayerPawn();

    UE_LOG(LogTemp, Warning, TEXT("Player exited vehicle"));

    OnPlayerExitVehicle.Broadcast(PC);
}

void ARomeroVehicle::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARomeroVehicle, OwningPlayerPawn);
}

void ARomeroVehicle::OnRep_OwningPlayerPawn()
{
    if (!IsValid(OwningPlayerPawn))
    {
        PlayerNameText->SetText(FText::GetEmpty());
        return;
    }

    if(!GetController())
    {
        UE_LOG(LogTemp, Error, TEXT("Vehicle has no owner"));
        return;
    }

    APlayerState* OwnPlayerState = GetController()->PlayerState;

    if (!IsValid(OwnPlayerState))
    {
        PlayerNameText->SetText(FText::GetEmpty());
        return;
    }

    PlayerNameText->SetText(FText::FromString(OwnPlayerState->GetPlayerName()));
}