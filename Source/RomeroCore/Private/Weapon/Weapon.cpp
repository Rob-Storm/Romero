#include "Weapon/Weapon.h"
#include "Net/UnrealNetwork.h"
#include "RomeroPlayer.h"
#include "Weapon/WeaponComponent.h"

void UWeapon::Server_UseItem_Implementation(ARomeroPlayer* OwningPlayer, EItemUseMode UseMode)
{
	TObjectPtr<UWeaponComponent> WeaponComponent = OwningPlayer->WeaponComponent;

	WeaponComponent->Server_Shoot();
}

void UWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UWeapon, CurrentAmmo);
	DOREPLIFETIME(UWeapon, ShootDelayActive);
}