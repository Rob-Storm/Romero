#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

#include "Inventory/ItemData.h"

#include "WeaponData.generated.h"

UCLASS(PrioritizeCategories = "Weapon Data")
class UWeaponData : public UItemData
{
	GENERATED_BODY()

public:

	UWeaponData();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Data")
	int32 Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Data")
	int32 Range;
	
};
