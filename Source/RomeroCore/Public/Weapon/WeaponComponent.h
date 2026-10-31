#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Weapon/Weapon.h"

#include "WeaponComponent.generated.h"


UCLASS(Blueprintable, BlueprintType)
class UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UWeaponComponent();

	UFUNCTION(Server, Reliable, BlueprintCallable, Category="Weapon")
	void Server_Shoot(class UWeaponData* WeaponData);

	UFUNCTION()
	bool ShootTrace(float Range, FHitResult &OutHitResult);
	
};