#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

#include "Inventory/Item.h"
#include "Weapon/WeaponData.h"

#include "Weapon.generated.h"

UCLASS(Blueprintable, BlueprintType)
class UWeapon : public UItem
{
	GENERATED_BODY()

public:

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="Weapon State")
	int32 CurrentAmmo;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="Weapon State")
	bool ShootDelayActive;

	UFUNCTION(BlueprintPure, BlueprintCallable, Category="Weapon State")
	bool CanShoot() const
	{
		return ShootDelayActive && CurrentAmmo > 0;
	}

	UFUNCTION(BlueprintPure, BlueprintCallable,Category="Item")
	UWeaponData* GetWeaponData() const
	{
		return Cast<UWeaponData>(ItemData);
	}

	virtual void UseItem_Implementation(ARomeroPlayer* OwningPlayer, EItemUseMode UseMode) override;
	
};
