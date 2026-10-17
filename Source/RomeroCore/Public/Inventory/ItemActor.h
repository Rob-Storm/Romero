#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/StaticMeshComponent.h"

#include "Interactable.h"
#include "Inventory/ItemData.h"

#include "ItemActor.generated.h"

UCLASS(meta = (PrioritizeCategories = "ItemActor"))
class AItemActor : public AActor, public IInteractable
{
	GENERATED_BODY()

public:

	AItemActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UStaticMeshComponent> Model;

	UPROPERTY(ReplicatedUsing = OnRep_ItemData, EditAnywhere, BlueprintReadWrite, Category="ItemActor")
	TObjectPtr<UItemData> ItemData;

	UFUNCTION(BlueprintCallable, Category="ItemActor")
	void SetItemData(UItemData* NewItemData);

	virtual void Interact_Implementation(class ARomeroPlayerController* CallingController) override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

private:

	UFUNCTION()
	void OnRep_ItemData();
	
};