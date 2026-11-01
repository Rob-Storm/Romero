#include "Nutrition/NutritionComponent.h"
#include "Net/UnrealNetwork.h"

#include "TimerManager.h"
#include "Math/UnrealMathUtility.h"

void UNutritionComponent::BeginPlay()
{
	Super::BeginPlay();

	// Hunger/Thirst are gameplay values that should ONLY be
	// adjusted on the server!
	if(!GetOwner()->HasAuthority())
	{
		return;
	}

	GetWorld()->GetTimerManager().SetTimer
	(
		HungerTimerHandle,
		this,
		&UNutritionComponent::TickHunger,
		HungerTickRate,
		true
    );

    GetWorld()->GetTimerManager().SetTimer
	(
		ThirstTimerHandle,
		this,
		&UNutritionComponent::TickThirst,
		ThirstTickRate,
		true
    );
}

void UNutritionComponent::Server_SetHunger_Implementation(int32 NewValue)
{
	CurrentHunger = FMath::Clamp(NewValue, 0, 100);
	OnRep_CurrentHunger();
}

void UNutritionComponent::Server_SetThirst_Implementation(int32 NewValue)
{
	CurrentThirst = FMath::Clamp(NewValue, 0, 100);
	OnRep_CurrentThirst();
}

void UNutritionComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UNutritionComponent, CurrentHunger);
	DOREPLIFETIME(UNutritionComponent, CurrentThirst);

	DOREPLIFETIME_CONDITION(UNutritionComponent, HungerTickRate, COND_InitialOnly);
	DOREPLIFETIME_CONDITION(UNutritionComponent, ThirstTickRate, COND_InitialOnly);
}

void UNutritionComponent::TickHunger()
{
	Server_SetHunger(CurrentHunger - 1);
	UE_LOG(LogTemp, Log, TEXT("CurrentHunger: %i"), CurrentHunger);
}

void UNutritionComponent::TickThirst()
{
	Server_SetThirst(CurrentThirst - 1);
	UE_LOG(LogTemp, Log, TEXT("CurrentThirst: %i"), CurrentThirst);
}

void UNutritionComponent::OnRep_CurrentHunger()
{
	OnHungerTicked.Broadcast(CurrentHunger);

	if(CurrentHunger <= 0)
	{
		OnStarve.Broadcast();
	}
}

void UNutritionComponent::OnRep_CurrentThirst()
{
	OnThirstTicked.Broadcast(CurrentThirst);

	if(CurrentThirst <= 0)
	{
		OnDehydrate.Broadcast();
	}
}