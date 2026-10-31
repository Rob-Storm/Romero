#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/StaticMeshActor.h"

#include "BuildableComponent.generated.h"

class UBuildableData;

/** Encapsulates the ability to create new ABuildableActors */
UCLASS(Blueprintable, BlueprintType)
class UBuildableComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UBuildableComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BuildableComponent")
	TObjectPtr<AStaticMeshActor> PreviewActor;

	/** Material used when a buildable can be placed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BuildableComponent")
	TObjectPtr<UMaterialInterface> BuildableMaterialGood;

	/** Material used when a buildable CAN'T be placed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BuildableComponent")
	TObjectPtr<UMaterialInterface> BuildableMaterialBad;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="BuildableComponent")
	void Build(const FTransform& Transform, UBuildableData* Data);	

	UFUNCTION(BlueprintCallable, Category="BuildableComponent")
	void PreviewBuilding(UBuildableData* Data);

	UFUNCTION()
	bool BuildingTrace(float Range, FHitResult &OutHitResult, FRotator &CameraRotation);

};
