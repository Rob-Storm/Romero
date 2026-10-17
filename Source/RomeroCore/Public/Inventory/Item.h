#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

#include "Inventory/ItemData.h"

#include "Item.generated.h"

/** Item representation in inventory */

UCLASS(Blueprintable, BlueprintType)
class UItem : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UItemData> ItemData;

	UFUNCTION(BlueprintPure, BlueprintCallable,Category="Item")
	UItemData* GetItemData() const
	{
		return ItemData;
	}

	virtual bool IsSupportedForNetworking() const override
	{
		return true;
	}

};