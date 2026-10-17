#include "RomeroPlayer.h"
#include "UObject/Object.h"

ARomeroPlayer::ARomeroPlayer()
{
	bReplicates = true;
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponComponent"));
	HeldWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HeldWeapon"));

	HeldWeapon->SetupAttachment(GetMesh(), FName(TEXT("WeaponSocket")));
}

void ARomeroPlayer::HandleWeaponChanged(UWeapon* weapon)
{
	HeldWeapon->SetStaticMesh(weapon->GetWeaponData()->WorldModel);
}

void ARomeroPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	WeaponComponent->OnWeaponChanged.AddDynamic(this, &ARomeroPlayer::HandleWeaponChanged);
}