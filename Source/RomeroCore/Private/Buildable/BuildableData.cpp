#include "Buildable/BuildableData.h"
#include "Buildable/Buildable.h"

UBuildableData::UBuildableData()
{
	ObjectClass = UBuildable::StaticClass();
	CanStack = true;
	MaxStackSize = 99;
	CanUse = false;
	CanEquip = true;
}