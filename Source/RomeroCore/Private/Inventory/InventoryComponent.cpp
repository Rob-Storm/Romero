#include "Inventory/InventoryComponent.h"
#include "UObject/Object.h"
#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"

#include "Inventory/ItemData.h"
#include "Inventory/ItemActor.h"

#include "RomeroPlayer.h"

UInventoryComponent::UInventoryComponent()
{
	SetIsReplicatedByDefault(true);
	bReplicateUsingRegisteredSubObjectList = true;
}

void UInventoryComponent::Server_AddItem_Implementation(UItemData* ItemData)
{
	if(!ItemData || !ItemData->ObjectClass)
	{
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Added Item ") + ItemData->ItemName.ToString());

	UItem* NewItem = NewObject<UItem>(this, ItemData->ObjectClass);
	NewItem->ItemData = ItemData;

	ItemList.Add(NewItem);
	AddReplicatedSubObject(NewItem);

	OnRep_ItemList();
}

void UInventoryComponent::Server_EquipItem_Implementation(UItem* Item)
{
	EquippedItem = Item;

	FString ItemName = !EquippedItem ? TEXT("None") : EquippedItem->GetItemData()->ItemName.ToString();

	UE_LOG(LogTemp, Log, TEXT("Equipped item %s"), *ItemName);
	OnRep_EquippedItem();
}

void UInventoryComponent::Server_RemoveItem_Implementation(UItem* Item)
{
	if(!Item)
	{
		return;
	}

	int32 RemoveItemIndex = ItemList.Find(Item);

	if(RemoveItemIndex == INDEX_NONE)
	{
		return;
	}

	if(Item == EquippedItem)
	{
		// unequip the equipped item before removing it
		Server_EquipItem(nullptr);
	}

	ItemList.RemoveAt(RemoveItemIndex);
	RemoveReplicatedSubObject(Item);

	OnRep_ItemList();
}

void UInventoryComponent::Server_SpawnItemActor_Implementation(UItem* Item)
{
	if(!Item)
	{
		return;
	}

	AActor* Owner = GetOwner();

	FHitResult Hit;

	FVector TraceStart = Owner->GetActorLocation();
	FVector TraceEnd = Owner->GetActorLocation() + (Owner->GetActorUpVector() * -1) * 1000.f;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(Owner);
	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECollisionChannel::ECC_Pawn, QueryParams);

	FVector SpawnLocation = Hit.Location;
	FRotator SpawnRotation = Owner->GetActorRotation();

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AItemActor* SpawnedItemActor = GetWorld()->SpawnActor<AItemActor>(AItemActor::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
	SpawnedItemActor->SetItemData(Item->ItemData);
	SpawnedItemActor->Model->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
}

void UInventoryComponent::Server_UseItem_Implementation(UItem* Item, EItemUseMode UseMode)
{
	if(!Item)
	{
		return;
	}
	
	TObjectPtr<ARomeroPlayer> Pawn = Cast<ARomeroPlayer>(GetOwner());

	if(!Pawn)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController not valid"));
		return;
	}

	Item->UseItem(Pawn, UseMode);

	if(Item->GetItemData()->CanStack)
	{
		Item->CurrentStackCount--;

		if(Item->CurrentStackCount <= 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Last count of item used, removing"));
			Server_RemoveItem(Item);
		}
	}
}

void UInventoryComponent::Server_UseEquippedItem_Implementation(EItemUseMode UseMode)
{
	if(!EquippedItem)
	{
		UE_LOG(LogTemp, Log, TEXT("No equipped item"));
		return;
	}

	Server_UseItem(EquippedItem, UseMode);
}

bool UInventoryComponent::HasItem(UItemData* ItemType, UItem* &OutFoundItem)
{
	OutFoundItem = nullptr;

	if(!ItemType)
	{
		return false;
	}

	for(UItem* Item : ItemList)
	{
		if(Item->ItemData == ItemType)
		{
			OutFoundItem = Item;
			return true;
		}
	}

	return false;
}

void UInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UInventoryComponent, ItemList);
	DOREPLIFETIME(UInventoryComponent, EquippedItem);
}

void UInventoryComponent::OnRep_ItemList()
{
	OnInventoryContentsChanged.Broadcast(ItemList);
	OnInventoryChanged.Broadcast();
}

void UInventoryComponent::OnRep_EquippedItem()
{
	OnEquippedItemChanged.Broadcast(EquippedItem);
}