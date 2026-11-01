#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Inventory/ItemData.h"

#include "NutritionData.generated.h"

UENUM(BlueprintType)
enum EPlayerStat
{
	Health,
	Stamina,
	Hunger,
	Thirst
};

USTRUCT(BlueprintType)
struct FStatModifier
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="NutritionData")
	TEnumAsByte<EPlayerStat> Stat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="NutritionData")
	int32 RestoreAmount;


};

UCLASS(PrioritizeCategories = "NutritionData")
class UNutritionData : public UItemData
{
	GENERATED_BODY()

public:

	UNutritionData();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="NutritionData")
	TArray<FStatModifier> StatModifiers;
	
};
