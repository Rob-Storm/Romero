#include "Inventory/InventoryComponent.h"
#include "UObject/Object.h"
#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"

#include "Inventory/ItemData.h"
#include "Inventory/ItemActor.h"

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

void UInventoryComponent::Server_RemoveItem_Implementation(UItem* Item)
{
	if(!Item)
	{
		return;
	}

	int32 RemoveItemIndex = ItemList.Find(Item);

	if(RemoveItemIndex == -1)
	{
		return;
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
}

void UInventoryComponent::OnRep_ItemList()
{
	OnInventoryContentsChanged.Broadcast(ItemList);
	OnInventoryChanged.Broadcast();
}