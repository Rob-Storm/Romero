#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Inventory/Item.h"

#include "NutritionItem.generated.h"

UCLASS()
class UNutritionItem : public UItem
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, BlueprintCallable,Category="Item")
	UNutritionData* GetNutritionData() const
	{
		return Cast<UNutritionData>(ItemData);
	}


	virtual void UseItem_Implementation(ARomeroPlayer* OwningPlayer, EItemUseMode UseMode) override;
	
};
