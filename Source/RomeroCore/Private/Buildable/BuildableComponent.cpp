#include "Buildable/BuildableComponent.h"
#include "Buildable/BuildableActor.h"
#include "Buildable/BuildableData.h"
#include "Net/UnrealNetwork.h"

UBuildableComponent::UBuildableComponent()
{
	SetIsReplicatedByDefault(true);
}

void UBuildableComponent::Server_SetBuildable_Implementation(UBuildable* Buildable)
{
	EquippedBuildable = Buildable;
	OnRep_EquippedBuildable();
}

void UBuildableComponent::Server_Build_Implementation(const FTransform& Transform)
{
    if (!EquippedBuildable)
    {
        return;
    }

    TObjectPtr<ABuildableActor> BuildableActor = GetWorld()->SpawnActorDeferred<ABuildableActor>
    (
    	ABuildableActor::StaticClass(), 
    	Transform,
    	GetOwner()
    );

    BuildableActor->Model = EquippedBuildable->GetBuildableData()->BuildableModel;
    BuildableActor->OnRep_Model();
    
    if (!BuildableActor)
    {
        UE_LOG(LogTemp, Warning, TEXT("Server_Build: SpawnActorDeferred failed"));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("Server_Build: ABuildableActor static mesh {%s}"), 
    	*GetNameSafe(EquippedBuildable->GetBuildableData()->BuildableModel));

    BuildableActor->FinishSpawning(Transform);

}

void UBuildableComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UBuildableComponent, EquippedBuildable);
}

void UBuildableComponent::OnRep_EquippedBuildable()
{
	OnBuildableChanged.Broadcast(EquippedBuildable);
}