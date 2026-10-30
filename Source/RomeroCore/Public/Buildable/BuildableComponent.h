#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "BuildableComponent.generated.h"

/** Encapsulates the ability to create new ABuildableActors */
UCLASS(Blueprintable, BlueprintType)
class UBuildableComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UBuildableComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RomeroCore")
	int32 SomeProperty;

	UFUNCTION(Server, Reliable, BlueprintCallable, Category="BuildableComponent")
	void Server_Build(const FTransform& Transform, class UBuildableData* Data);	
};
