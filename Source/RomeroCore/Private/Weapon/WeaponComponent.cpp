#include "Weapon/WeaponComponent.h"
#include "Net/UnrealNetwork.h"

UWeaponComponent::UWeaponComponent()
{
	SetIsReplicatedByDefault(true);
}


void UWeaponComponent::Server_WeaponTrace_Implementation()
{

}

void UWeaponComponent::Server_Shoot_Implementation()
{
	
}