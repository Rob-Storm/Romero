#include "RomeroPlayer.h"
#include "UObject/Object.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "RomeroPlayerState.h"

ARomeroPlayer::ARomeroPlayer()
{
	bReplicates = true;
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponComponent"));
	BuildComponent = CreateDefaultSubobject<UBuildableComponent>(TEXT("BuildComponent"));
	NutritionComponent = CreateDefaultSubobject<UNutritionComponent>(TEXT("NutritionComponent"));
	StaminaComponent = CreateDefaultSubobject<UStaminaComponent>(TEXT("StaminaComponent"));

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
	NutritionComponent->OnStarve.AddDynamic(this, &ARomeroPlayer::HandleNutritionEmpty);
	NutritionComponent->OnDehydrate.AddDynamic(this, &ARomeroPlayer::HandleNutritionEmpty);
	StaminaComponent->OnStartSprint.AddDynamic(this, &ARomeroPlayer::Server_HandleSprintStarted);
	StaminaComponent->OnEndSprint.AddDynamic(this, &ARomeroPlayer::Server_HandleSprintEnded);
}

void ARomeroPlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARomeroPlayer, PawnName);
	DOREPLIFETIME(ARomeroPlayer, IsSprinting);
}

void ARomeroPlayer::OnRep_SetPawnName()
{
	PlayerNameText->SetText(FText::FromString(PawnName));
}

void ARomeroPlayer::OnRep_IsSprinting()
{
	GetCharacterMovement()->MaxWalkSpeed = IsSprinting ? 500.f : 250.f;
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

void ARomeroPlayer::HandleNutritionEmpty()
{
	HealthComponent->Server_AddHealth(-10);
}

void ARomeroPlayer::Server_HandleSprintStarted_Implementation()
{
	IsSprinting = true;
	OnRep_IsSprinting();
}

void ARomeroPlayer::Server_HandleSprintEnded_Implementation()
{
	IsSprinting = false;
	OnRep_IsSprinting();
}