#include "Buildable/Buildable.h"
#include "Buildable/BuildableComponent.h"
#include "RomeroPlayer.h"

void UBuildable::Server_UseItem_Implementation(ARomeroPlayer* OwningPlayer, EItemUseMode UseMode)
{
	TObjectPtr<UBuildableComponent> BuildableComponent = OwningPlayer->BuildComponent;

	BuildableComponent->Server_Build();
}