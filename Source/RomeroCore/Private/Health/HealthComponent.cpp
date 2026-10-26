#include "Health/HealthComponent.h"
#include "Net/UnrealNetwork.h"

UHealthComponent::UHealthComponent()
{
	SetIsReplicatedByDefault(true);
}

void UHealthComponent::Server_AddHealth_Implementation(int32 amount)
{
	CurrentHealth += amount;
	OnRep_CurentHealth();
}
	
void UHealthComponent::Server_Kill_Implementation()
{
	CurrentHealth = 0;
	OnRep_CurentHealth();
}

void UHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UHealthComponent, CurrentHealth);
}
	
void UHealthComponent::OnRep_CurentHealth()
{
	OnHealthChanged.Broadcast(CurrentHealth);

	
	if(CurrentHealth <= 0)
	{
		CurrentHealth = 0;
		OnKilled.Broadcast();
	}
}