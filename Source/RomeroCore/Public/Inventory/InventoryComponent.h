#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Inventory/Item.h"

#include "InventoryComponent.generated.h"

class UItemData;

// Containers must be passed by a const ref or else they will throw blueprint compiler errors about mismatched signatures!
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInventoryContentsChangedSignature, const TArray<UItem*>&, ItemList);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryChangedSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEquippedItemChangedSignature, UItem*, EquippedItem);

UCLASS(Blueprintable, BlueprintType)
class UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UInventoryComponent();

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Inventory")
	FOnInventoryContentsChangedSignature OnInventoryContentsChanged;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Inventory")
	FOnInventoryChangedSignature OnInventoryChanged;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Inventory")
	FOnEquippedItemChangedSignature OnEquippedItemChanged;

	UPROPERTY(ReplicatedUsing = OnRep_EquippedItem, EditAnywhere, BlueprintReadWrite, Category="Inventory")
	TObjectPtr<UItem> EquippedItem;

	UPROPERTY(ReplicatedUsing = OnRep_ItemList, EditAnywhere, BlueprintReadWrite, Category="Inventory")
	TArray<UItem*> ItemList;

	UFUNCTION(Server, Reliable, BlueprintCallable, Category="Inventory")
	void Server_AddItem(UItemData* ItemData);

	UFUNCTION(Server, Reliable, BlueprintCallable, Category="Inventory")
	void Server_EquipItem(UItem* Item);

	UFUNCTION(Server, Reliable, BlueprintCallable, Category="Inventory")
	void Server_RemoveItem(UItem* Item);

	UFUNCTION(Server, Reliable, BlueprintCallable, Category="Inventory")
	void Server_SpawnItemActor(UItem* Item);

	UFUNCTION(Server, Reliable, BlueprintCallable, Category="Inventory")
	void Server_UseItem(UItem* Item, EItemUseMode UseMode);

	UFUNCTION(Server, Reliable, BlueprintCallable, Category="Inventory")
	void Server_UseEquippedItem(EItemUseMode UseMode);

	/** Checks if an item containing the ItemData exists and returns the first instance found. Using nullptr or none will always return false */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool HasItem(UItemData* ItemType, UItem* &OutFoundItem);

	UFUNCTION(BlueprintCallable, Category="Inventory")
	UItem* GetEquippedItem() const
	{
		return EquippedItem;
	}

private:

	UFUNCTION()
	void OnRep_ItemList();

	UFUNCTION()
	void OnRep_EquippedItem();
	
};