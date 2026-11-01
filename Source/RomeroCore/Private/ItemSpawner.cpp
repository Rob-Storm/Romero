#include "ItemSpawner.h"
#include "UObject/Object.h"
#include "TimerManager.h"

#include "Inventory/ItemActor.h"

AItemSpawner::AItemSpawner()
{
	BillboardComponent = CreateDefaultSubobject<UBillboardComponent>(TEXT("BillboardComponent"));
	RootComponent = BillboardComponent;
}

void AItemSpawner::BeginPlay()
{
	Super::BeginPlay();

	SpawnItem();
}

void AItemSpawner::SpawnItem_Implementation()
{
    if (!HasAuthority())
    {
    	return;
    }

    if (ItemClasses.IsEmpty())
    {
        return;
    }

    const int32 Index = FMath::RandRange(0, ItemClasses.Num() - 1);

    UWorld* World = GetWorld();

    if (!World)
    {
        return;
    }

    FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AItemActor* SpawnedItemActor = GetWorld()->SpawnActor<AItemActor>
	(
		AItemActor::StaticClass(), 
		GetActorLocation(), 
		GetActorRotation(), 
		SpawnParams
	);

	if(!SpawnedItemActor)
	{
		return;
	}

    SpawnedItem = SpawnedItemActor;

    SpawnedItemActor->SetOwner(this);

	SpawnedItemActor->SetItemData(ItemClasses[Index]);
	SpawnedItemActor->Model->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	SpawnedItem->OnDestroyed.AddDynamic(this, &AItemSpawner::OnItemDestroyed);
}

void AItemSpawner::OnItemDestroyed(AActor* DestroyedActor)
{
	GetWorldTimerManager().SetTimer
	(
		RespawnTimerHandle,
		this,
		&AItemSpawner::SpawnItem,
		RespawnDelay,
		false
	);
}