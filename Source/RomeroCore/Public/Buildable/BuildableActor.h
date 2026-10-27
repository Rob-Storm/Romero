#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"

#include "Damageable.h"
#include "Health/HealthComponent.h"

#include "Serializable.h"

#include "BuildableActor.generated.h"

UCLASS()
class ABuildableActor : public AActor, public IDamageable, public ISerializeable
{
	GENERATED_BODY()

public:

	ABuildableActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UHealthComponent> HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(ReplicatedUsing = OnRep_Model, EditAnywhere, BlueprintReadWrite, Category="Components", meta = (ExposeOnSpawn="true"), SaveGame)
	TObjectPtr<UStaticMesh> Model;

	UFUNCTION()
	void OnRep_Model();

	virtual void OnActorLoaded_Implementation() override;

protected:

	virtual void BeginPlay() override;
};
