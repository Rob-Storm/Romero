#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "ItemData.generated.h"

UCLASS()
class UItemData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	FText ItemName = FText::FromString(this->GetName());

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	FText ItemDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	TSubclassOf<class UItem> ObjectClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	TObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	TObjectPtr<UStaticMesh> WorldModel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	bool CanStack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item", meta=(EditCondition = "CanStack", ClampMin = "1", UIMin = "1"))
	int32 MaxStackSize = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	FIntPoint ItemSize = FIntPoint(1,1);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	bool CanUse = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	bool CanEquip = false;
	
};
