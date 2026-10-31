#include "Inventory/Item.h"
#include "Net/UnrealNetwork.h"
#include "RomeroPlayer.h"
#include "GameFramework/PlayerState.h"

void UItem::UseItem_Implementation(ARomeroPlayer* OwningPlayer, EItemUseMode UseMode)
{
	TObjectPtr<APlayerState> PS = OwningPlayer->GetController()->PlayerState;

	UE_LOG(LogTemp, Log, TEXT("%s used Item %s"), *PS->GetPlayerName(), *ItemData->ItemName.ToString());
}

void UItem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UItem, ItemData);
	DOREPLIFETIME(UItem, CurrentStackCount);
}