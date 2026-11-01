#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/BillboardComponent.h"

#include "Inventory/ItemData.h"

#include "ItemSpawner.generated.h"

UCLASS(Blueprintable, BlueprintType, PrioritizeCategories = "ItemSpawner")
class AItemSpawner : public AActor
{
	GENERATED_BODY()

public:

	AItemSpawner();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UBillboardComponent> BillboardComponent;

	/** The items that can potentially spawn from this actor */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ItemSpawner")
	TArray<TObjectPtr<UItemData>> ItemClasses;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="ItemSpawner")
	void SpawnItem();

	virtual void BeginPlay() override;
};
