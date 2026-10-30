#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Inventory/Item.h"
#include "Buildable/BuildableData.h"

#include "Buildable.generated.h"

UCLASS()
class UBuildable : public UItem
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, BlueprintCallable,Category="Item")
	UBuildableData* GetBuildableData() const
	{
		return Cast<UBuildableData>(ItemData);
	}

	virtual void Server_UseItem_Implementation(ARomeroPlayer* OwningPlayer, EItemUseMode UseMode) override;
};
