#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Buildable/Buildable.h"

#include "BuildableComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildableChangedSignature, UBuildable*, EquippedBuildable);


/** Encapsulates the ability to create new ABuildableActors */
UCLASS(Blueprintable, BlueprintType)
class UBuildableComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UBuildableComponent();

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="BuildableComponent")
	FOnBuildableChangedSignature OnBuildableChanged;

	UPROPERTY(ReplicatedUsing = OnRep_EquippedBuildable, EditAnywhere, BlueprintReadWrite, Category="BuildableComponent")
	TObjectPtr<UBuildable> EquippedBuildable;

	UFUNCTION(Server, Reliable, BlueprintCallable, Category="BuildableComponent")
	void Server_SetBuildable(UBuildable* Buildable);

	UFUNCTION(Server, Reliable, BlueprintCallable, Category="BuildableComponent")
	void Server_Build(const FTransform& Transform);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:

	UFUNCTION()
	void OnRep_EquippedBuildable();
	
};
