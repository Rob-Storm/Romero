#include "Weapon/Weapon.h"
#include "Net/UnrealNetwork.h"
#include "RomeroPlayer.h"
#include "Weapon/WeaponComponent.h"

void UWeapon::UseItem_Implementation(ARomeroPlayer* OwningPlayer, EItemUseMode UseMode)
{
	TObjectPtr<UWeaponComponent> WeaponComponent = OwningPlayer->WeaponComponent;

	WeaponComponent->Server_Shoot(GetWeaponData());
}

void UWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UWeapon, CurrentAmmo);
	DOREPLIFETIME(UWeapon, ShootDelayActive);
}