#include "Nutrition/NutritionItem.h"
#include "Nutrition/NutritionComponent.h"
#include "Nutrition/NutritionData.h"
#include "Health/HealthComponent.h"
#include "Stamina/StaminaComponent.h"
#include "RomeroPlayer.h"

void UNutritionItem::UseItem_Implementation(ARomeroPlayer* OwningPlayer, EItemUseMode UseMode)
{
	Super::UseItem_Implementation(OwningPlayer, UseMode);

	if(UseMode != EItemUseMode::Primary)
	{
		return;
	}

	for(const auto &StatModifier : GetNutritionData()->StatModifiers)
	{
		int32 Amount = StatModifier.RestoreAmount;
		switch(StatModifier.Stat)
		{
			case EPlayerStat::Health:
				OwningPlayer->HealthComponent->Server_AddHealth(Amount);
				break;
			case EPlayerStat::Stamina:
				OwningPlayer->StaminaComponent->Server_SetStamina_Implementation(OwningPlayer->StaminaComponent->CurrentStamina + Amount);
				break;
			case EPlayerStat::Hunger:
				OwningPlayer->NutritionComponent->Server_SetHunger(OwningPlayer->NutritionComponent->CurrentHunger + Amount);
				break;
			case EPlayerStat::Thirst:
				OwningPlayer->NutritionComponent->Server_SetThirst(OwningPlayer->NutritionComponent->CurrentThirst + Amount);
				break;
		}
	}

}