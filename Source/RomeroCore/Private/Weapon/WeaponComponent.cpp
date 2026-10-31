#include "Weapon/WeaponComponent.h"
#include "Net/UnrealNetwork.h"

#include "RomeroPlayer.h"
#include "RomeroPlayerController.h"
#include "Weapon/WeaponData.h"
#include "Damageable.h"

#include "Camera/PlayerCameraManager.h"
#include "GameFramework/PlayerController.h"

UWeaponComponent::UWeaponComponent()
{
	SetIsReplicatedByDefault(true);
}


void UWeaponComponent::Server_Shoot_Implementation(UWeaponData* WeaponData)
{
    FHitResult Result;

	if(ShootTrace(WeaponData->Range, Result))
	{
		TObjectPtr<AActor> HitActor = Result.GetActor();

		if(!HitActor)
		{
			return;
		}

		if(!HitActor->Implements<UDamageable>())
		{
			return;
		}

		TObjectPtr<ARomeroPlayer> Pawn = Cast<ARomeroPlayer>(GetOwner());
	
    	if(!Pawn)
    	{
    	    return;
    	}
	
    	ARomeroPlayerController* PC = Cast<ARomeroPlayerController>(Pawn->GetController());
    	
    	if(!PC)
    	{
    	    return;
    	}

		IDamageable::Execute_Damage(HitActor, PC, WeaponData);

		// apply physics to actor for funny ragdoll effects

		// play effects like sounds/particle effects (use netmulticast rpc)
	}
}


bool UWeaponComponent::ShootTrace(float Range, FHitResult &OutHitResult)
{
    FVector StartLocation;
    FVector EndLocation;
    FRotator CameraRotation;
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