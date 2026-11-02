#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/NavigationObjectBase.h"
#include "RomeroCharacter.h"

#include "Components/BillboardComponent.h"
#include "Components/ArrowComponent.h"

#include "ZombieSpawner.generated.h"

UCLASS(Blueprintable, BlueprintType, PrioritizeCategories = "ZombieSpawner")
class AZombieSpawner : public ANavigationObjectBase
{
	GENERATED_BODY()

public:

	AZombieSpawner();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UArrowComponent> ArrowComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ZombieSpawner")
	float RespawnDelay = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ZombieSpawner")
	TSubclassOf<ARomeroCharacter> ZombieClass;

	UPROPERTY()
	TObjectPtr<ARomeroCharacter> SpawnedZombie;

	UPROPERTY()
	FTimerHandle RespawnTimerHandle;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="ZombieSpawner")
	void SpawnZombie();

	UFUNCTION()
	void OnZombieKilled();

	virtual void BeginPlay() override;
};
