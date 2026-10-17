#include "Inventory/Item.h"
#include "Net/UnrealNetwork.h"

void UItem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UItem, ItemData);
}