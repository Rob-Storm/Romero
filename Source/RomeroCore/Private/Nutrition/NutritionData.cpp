#include "Nutrition/NutritionData.h"
#include "Nutrition/NutritionItem.h"

UNutritionData::UNutritionData()
{
	CanStack = true;
	CanUse = true;
	CanEquip = true;
	MaxStackSize = 10;
	ObjectClass = UNutritionItem::StaticClass();
}