#include "Stamina/StaminaComponent.h"
#include "Net/UnrealNetwork.h"

#include "TimerManager.h"
#include "Math/UnrealMathUtility.h"

UStaminaComponent::UStaminaComponent()
{
	SetIsReplicatedByDefault(true);
}

void UStaminaComponent::Server_StartSprint_Implementation()
{
	GetWorld()->GetTimerManager().ClearTimer(RecoverHandle);
	GetWorld()->GetTimerManager().ClearTimer(RecoverDelayHandle);

	GetWorld()->GetTimerManager().SetTimer
	(
		SprintHandle,
		this,
		&UStaminaComponent::TickStaminaDown,
		StaminaConsumptionRate,
		true
    );

	OnStartSprint.Broadcast();
}

void UStaminaComponent::Server_EndSprint_Implementation()
{
	GetWorld()->GetTimerManager().ClearTimer(SprintHandle);

	GetWorld()->GetTimerManager().SetTimer
	(
		RecoverDelayHandle,
		this,
		&UStaminaComponent::BeginStaminaRecovery,
		RecoverDelay,
		false
    );

	OnEndSprint.Broadcast();
}

void UStaminaComponent::Server_SetStamina_Implementation(int32 NewAmount)
{
	CurrentStamina = FMath::Clamp(NewAmount, 0, 100);
	OnRep_CurrentStamina();
}

void UStaminaComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UStaminaComponent, CurrentStamina);

	DOREPLIFETIME_CONDITION(UStaminaComponent, RecoverDelay, COND_InitialOnly);
	DOREPLIFETIME_CONDITION(UStaminaComponent, RecoverRate, COND_InitialOnly);
	DOREPLIFETIME_CONDITION(UStaminaComponent, StaminaConsumptionRate, COND_InitialOnly);
}

void UStaminaComponent::BeginStaminaRecovery()
{
	GetWorld()->GetTimerManager().SetTimer
	(
		RecoverHandle,
		this,
		&UStaminaComponent::TickStaminaUp,
		RecoverRate,
		true
    );
}

void UStaminaComponent::TickStaminaUp()
{
	Server_SetStamina(CurrentStamina + 1);

	if(CurrentStamina >= 100)
	{
		GetWorld()->GetTimerManager().ClearTimer(RecoverHandle);
	}
}

void UStaminaComponent::TickStaminaDown()
{
	Server_SetStamina(CurrentStamina - 1);

	if(CurrentStamina <= 0)
	{
		Server_EndSprint();
	}
}

void UStaminaComponent::OnRep_CurrentStamina()
{
	OnStaminaChanged.Broadcast(CurrentStamina);
}