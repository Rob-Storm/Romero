#include "RomeroPlayer.h"
#include "UObject/Object.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"
#include "RomeroPlayerState.h"

ARomeroPlayer::ARomeroPlayer()
{
	bReplicates = true;
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponComponent"));
	BuildComponent = CreateDefaultSubobject<UBuildableComponent>(TEXT("BuildComponent"));

	PlayerNameText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("PlayerName"));

	HeldWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HeldWeapon"));

	HeldWeapon->SetupAttachment(GetMesh(), FName(TEXT("WeaponSocket")));
	PlayerNameText->SetupAttachment(RootComponent);
}

void ARomeroPlayer::HandleWeaponChanged(UWeapon* Weapon)
{
	if(!Weapon)
	{
		HeldWeapon->SetVisibility(false);
		return;
	}

	HeldWeapon->SetVisibility(true);

	HeldWeapon->SetStaticMesh(Weapon->GetWeaponData()->WorldModel);
}

void ARomeroPlayer::Server_SetPlayerText_Implementation()
{
	TObjectPtr<APlayerController> PC = Cast<APlayerController>(GetOwner());

	if(!PC)
	{
		return;
	}

	TObjectPtr<APlayerState> PS = Cast<APlayerState>(PC->PlayerState);

	if(!PS)
	{
		return;
	}

	PawnName = PS->GetPlayerName();
	OnRep_SetPawnName();
}

void ARomeroPlayer::BeginPlay()
{
	Super::BeginPlay();

	Server_SetPlayerText();

	TObjectPtr<APlayerController> PC = Cast<APlayerController>(GetOwner());

	if(!PC)
	{
		return;
	}

	TObjectPtr<ARomeroPlayerState> PS = Cast<ARomeroPlayerState>(PC->PlayerState);

	if(!PS)
	{
		return;
	}

	if(!PS->QuitDead)
	{
		SetActorTransform(PS->LastSpawnTransform, false, nullptr, ETeleportType::TeleportPhysics);
	}
}

void ARomeroPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	WeaponComponent->OnWeaponChanged.AddDynamic(this, &ARomeroPlayer::HandleWeaponChanged);
}

void ARomeroPlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARomeroPlayer, PawnName);
}


void ARomeroPlayer::OnRep_SetPawnName()
{
	PlayerNameText->SetText(FText::FromString(PawnName));
}