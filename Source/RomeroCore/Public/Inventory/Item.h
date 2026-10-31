#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

#include "Inventory/ItemData.h"

#include "Item.generated.h"

class ARomeroPlayer;

UENUM(BlueprintType)
enum EItemUseMode
{
	Primary, // left click
	Secondary, // right click
	Tertiary // other, R or another key
};

/** Runtime representation of an inventory item  */

UCLASS(Blueprintable, BlueprintType)
class UItem : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UItemData> ItemData;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="RomeroCore")
	int32 CurrentStackCount = 1;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Item")
	void UseItem(ARomeroPlayer* OwningPlayer, EItemUseMode UseMode);

	virtual void UseItem_Implementation(ARomeroPlayer* OwningPlayer, EItemUseMode UseMode);

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