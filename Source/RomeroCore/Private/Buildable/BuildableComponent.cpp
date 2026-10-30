#include "Buildable/BuildableComponent.h"
#include "Buildable/Buildable.h"
#include "Buildable/BuildableActor.h"
#include "Buildable/BuildableData.h"
#include "Net/UnrealNetwork.h"

UBuildableComponent::UBuildableComponent()
{
	SetIsReplicatedByDefault(true);
}

void UBuildableComponent::Server_Build_Implementation(const FTransform& Transform, UBuildableData* Data)
{
    if (!Data)
    {
        return;
    }

    TObjectPtr<ABuildableActor> BuildableActor = GetWorld()->SpawnActorDeferred<ABuildableActor>
    (
    	ABuildableActor::StaticClass(), 
    	Transform,
    	GetOwner()
    );

    BuildableActor->Model = Data->BuildableModel;
    BuildableActor->OnRep_Model();
    
    if (!BuildableActor)
    {
        UE_LOG(LogTemp, Warning, TEXT("Server_Build: SpawnActorDeferred failed"));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("Server_Build: ABuildableActor static mesh {%s}"), 
        *GetNameSafe(Data->BuildableModel));

    BuildableActor->FinishSpawning(Transform);

}