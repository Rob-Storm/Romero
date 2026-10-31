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

	FirstPersonItem = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FirstPersonItem"));
	ThirdPersonItem = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ThirdPersonItem"));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	PlayerNameText->SetupAttachment(RootComponent);
	Camera->SetupAttachment(RootComponent);

	ThirdPersonItem->SetupAttachment(GetMesh(), FName(TEXT("WeaponSocket")));
	FirstPersonItem->SetupAttachment(Camera);
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
}

void ARomeroPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	InventoryComponent->OnEquippedItemChanged.AddDynamic(this, &ARomeroPlayer::HandleItemChanged);
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

void ARomeroPlayer::HandleItemChanged(UItem* EquippedItem)
{
	TObjectPtr<UStaticMesh> NewMesh = nullptr;

	if(IsValid(EquippedItem))
	{
		NewMesh = EquippedItem->GetItemData()->WorldModel;
	}

	FirstPersonItem->SetStaticMesh(NewMesh);
	ThirdPersonItem->SetStaticMesh(NewMesh);
}