#include "Buildable/BuildableComponent.h"

#include "Buildable/Buildable.h"
#include "Buildable/BuildableActor.h"
#include "Buildable/BuildableData.h"
#include "RomeroPlayer.h"

#include "Net/UnrealNetwork.h"
#include "Camera/CameraComponent.h"

#include "Camera/PlayerCameraManager.h"
#include "GameFramework/PlayerController.h"

UBuildableComponent::UBuildableComponent()
{
	SetIsReplicatedByDefault(true);
}

void UBuildableComponent::Build_Implementation(const FTransform& Transform, UBuildableData* Data)
{
    UE_LOG(LogTemp, Warning, TEXT("Server_Build executed. Authority: %d"), GetOwner()->HasAuthority());

    if (!Data)
    {
        UE_LOG(LogTemp, Warning, TEXT("Server_Build: buildable data invalid"));
        return;
    }

    TObjectPtr<ABuildableActor> BuildableActor = GetWorld()->SpawnActorDeferred<ABuildableActor>
    (
    	ABuildableActor::StaticClass(), 
    	Transform,
    	GetOwner()
    );

    if(!BuildableActor)
    {
        return;
    }

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

void UBuildableComponent::PreviewBuilding(UBuildableData* Data)
{
    FHitResult Result;
    FRotator CameraRotation;

    if(BuildingTrace(500.f, Result, CameraRotation))
    {
        FRotator ModelRotation(0.f, CameraRotation.Yaw, 0.f);

        if(!IsValid(PreviewActor))
        {
            FTransform SpawnTransform(CameraRotation.Quaternion(), Result.ImpactPoint, FVector::OneVector);

            PreviewActor = GetWorld()->SpawnActorDeferred<AStaticMeshActor>
            (
                AStaticMeshActor::StaticClass(),
                SpawnTransform,
                GetOwner()
            );

            PreviewActor->GetRootComponent()->SetMobility(EComponentMobility::Movable);
            PreviewActor->SetActorEnableCollision(false);
            PreviewActor->GetStaticMeshComponent()->SetMaterial(0, BuildableMaterialGood);

            PreviewActor->FinishSpawning(SpawnTransform);
        }

        PreviewActor->SetActorLocationAndRotation(Result.ImpactPoint, ModelRotation);

        PreviewActor->GetStaticMeshComponent()->SetStaticMesh(Data->BuildableModel);
        PreviewActor->SetActorHiddenInGame(false);
    }
    else if(IsValid(PreviewActor))
    {
        PreviewActor->SetActorHiddenInGame(true);
    }
}

bool UBuildableComponent::BuildingTrace(float Range, FHitResult &OutHitResult, FRotator &CameraRotation)
{
    FVector StartLocation;
    FVector EndLocation;
    FHitResult Result;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(GetOwner());
    FCollisionResponseParams ResponseParams;

    TObjectPtr<ARomeroPlayer> Pawn = Cast<ARomeroPlayer>(GetOwner());

    if(!Pawn)
    {
        return false;
    }

    APlayerController* PC = Cast<APlayerController>(Pawn->GetController());
    
    if(!PC)
    {
        return false;
    }
    
    APlayerCameraManager* CameraManager = PC->PlayerCameraManager;
    
    if(!CameraManager)
    {
        return false;
    }
    
    StartLocation = CameraManager->GetCameraLocation();
    CameraRotation = CameraManager->GetCameraRotation();
    
    EndLocation = StartLocation + (CameraRotation.Vector() * Range);

    GetWorld()->LineTraceSingleByChannel(Result, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility, QueryParams, ResponseParams);

    OutHitResult = Result;

    return Result.bBlockingHit;
}