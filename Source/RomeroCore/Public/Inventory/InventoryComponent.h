#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Inventory/Item.h"

#include "InventoryComponent.generated.h"

class UItemData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInventoryContentsChangedSignature, TArray<UItem*>, ItemList);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryChangedSignature);

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

	UPROPERTY(ReplicatedUsing = OnRep_ItemList, EditAnywhere, BlueprintReadWrite, Category="Inventory")
	TArray<UItem*> ItemList;

	UFUNCTION(Server, Reliable, BlueprintCallable, Category="Inventory")
	void Server_AddItem(UItemData* ItemData);

	UFUNCTION(Server, Reliable, BlueprintCallable, Category="Inventory")
	void Server_RemoveItem(UItem* Item);

	UFUNCTION(Server, Reliable, BlueprintCallable, Category="Inventory")
	void Server_SpawnItemActor(UItem* Item);

	/** Checks if an item containing the ItemData exists and returns the first instance found. Using nullptr or none will always return false */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool HasItem(UItemData* ItemType, UItem* &OutFoundItem);

private:

	UFUNCTION()
	void OnRep_ItemList();
	
};