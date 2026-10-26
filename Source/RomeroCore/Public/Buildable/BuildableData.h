#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Inventory/ItemData.h"

#include "BuildableData.generated.h"

UCLASS(PrioritizeCategories="BuildableData")
class UBuildableData : public UItemData
{
	GENERATED_BODY()

public:

	UBuildableData();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	TObjectPtr<UStaticMesh> BuildableModel;
	
};
