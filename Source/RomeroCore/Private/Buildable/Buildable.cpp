#include "Buildable/Buildable.h"
#include "Buildable/BuildableComponent.h"
#include "RomeroPlayer.h"

void UBuildable::UseItem_Implementation(ARomeroPlayer* OwningPlayer, EItemUseMode UseMode)
{
    // make sure you call the _Implementation version!
    // you will get an infinite loop otherwise
    Super::UseItem_Implementation(OwningPlayer, UseMode);

	TObjectPtr<UBuildableComponent> BuildableComponent = OwningPlayer->BuildComponent;

	FHitResult Result;
    FRotator CameraRotation;

    if(BuildableComponent->BuildingTrace(500.f, Result, CameraRotation))
    {
    	FRotator SpawnRotation(0.f, CameraRotation.Yaw, 0.f);
    	FTransform SpawnTransform(SpawnRotation.Quaternion(), Result.ImpactPoint, FVector::OneVector);
    	BuildableComponent->Build(SpawnTransform, GetBuildableData());
    }
}