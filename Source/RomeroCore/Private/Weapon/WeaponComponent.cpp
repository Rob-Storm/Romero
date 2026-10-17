#include "Weapon/WeaponComponent.h"
#include "Net/UnrealNetwork.h"

UWeaponComponent::UWeaponComponent()
{
	SetIsReplicatedByDefault(true);
}

void UWeaponComponent::Server_SetWeapon_Implementation(UWeapon* NewWeapon)
{
	CurrentWeapon = NewWeapon;
	OnRep_CurrentWeapon();
}

void UWeaponComponent::Server_WeaponTrace_Implementation()
{

}

void UWeaponComponent::Server_Shoot_Implementation()
{
	
}

void UWeaponComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UWeaponComponent, CurrentWeapon);
}

void UWeaponComponent::OnRep_CurrentWeapon()
{
	OnWeaponChanged.Broadcast(CurrentWeapon);
}