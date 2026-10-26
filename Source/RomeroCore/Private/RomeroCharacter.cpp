#include "RomeroCharacter.h"
#include "UObject/Object.h"

#include "RomeroPlayerController.h"
#include "Weapon/WeaponData.h"

#include "Components/CapsuleComponent.h"

ARomeroCharacter::ARomeroCharacter()
{
	bReplicates = true;
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

void ARomeroCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	HealthComponent->OnHealthChanged.AddDynamic(this, &ARomeroCharacter::HandleHealthChanged);
	HealthComponent->OnKilled.AddDynamic(this, &ARomeroCharacter::HandleKilled);
}

void ARomeroCharacter::Damage_Implementation(ARomeroPlayerController* CallingController, UWeaponData* Weapon)
{
	HealthComponent->Server_AddHealth(-(Weapon->Damage));
}

void ARomeroCharacter::HandleHealthChanged(int32 CurrentHealth)
{
	/* Do something */
}

void ARomeroCharacter::HandleKilled()
{
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetSimulatePhysics(true);
}