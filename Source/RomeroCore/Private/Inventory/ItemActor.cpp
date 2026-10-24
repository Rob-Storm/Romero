#include "Inventory/ItemActor.h"
#include "UObject/Object.h"
#include "Net/UnrealNetwork.h"

#include "GameFramework/Character.h"
#include "RomeroPlayerController.h"
#include "RomeroPlayer.h"

AItemActor::AItemActor()
{
	bReplicates = true;
	
	Model = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Model"));

	Model->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	Model->SetCollisionResponseToChannel(ECollisionChannel::ECC_Vehicle, ECollisionResponse::ECR_Ignore);

	RootComponent = Model;
}

void AItemActor::SetItemData(UItemData* NewItemData)
{
	ItemData = NewItemData;
	Model->SetStaticMesh(ItemData->WorldModel);

	OnRep_ItemData();
}

void AItemActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AItemActor, ItemData);
}

void AItemActor::Interact_Implementation(ARomeroPlayerController* CallingController)
{
	ARomeroPlayer* Player = Cast<ARomeroPlayer>(CallingController->GetPawn());

	if(!ItemData)
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemData was not valid"));
		return;
	}

	if(!Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("Controller pawn was not an ARomeroPlayer"));
		return;
	}

	if(Player)
	{
		Player->InventoryComponent->Server_AddItem(ItemData);
		Destroy();
	}

}

#if WITH_EDITOR

void AItemActor::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName PropertyName = (PropertyChangedEvent.Property != nullptr)
		? PropertyChangedEvent.Property->GetFName()
		: NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(AItemActor, ItemData))
	{
		if (ItemData && Model)
		{
			Model->SetStaticMesh(ItemData->WorldModel);
		}
	}
}

#endif

void AItemActor::OnRep_ItemData()
{
	Model->SetStaticMesh(ItemData->WorldModel);
}