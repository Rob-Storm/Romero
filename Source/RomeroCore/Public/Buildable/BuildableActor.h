#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"

#include "Damageable.h"
#include "Health/HealthComponent.h"

#include "BuildableActor.generated.h"

UCLASS()
class ABuildableActor : public AActor, public IDamageable
{
	GENERATED_BODY()

public:

	ABuildableActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UHealthComponent> HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(ReplicatedUsing = OnRep_Model, EditAnywhere, BlueprintReadWrite, Category="Components", meta = (ExposeOnSpawn="true"))
	TObjectPtr<UStaticMesh> Model;

	UFUNCTION()
	void OnRep_Model();

protected:

	virtual void BeginPlay() override;
};
