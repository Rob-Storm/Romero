#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "NutritionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHungerTickedSignature, int32, CurrentHunger);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnThirstTickedSignature, int32, CurrentThirst);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStarveSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDehydrateSignature);

UCLASS(Blueprintable, BlueprintType)
class UNutritionComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="NutritionComponent")
	FOnHungerTickedSignature OnHungerTicked;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="NutritionComponent")
	FOnThirstTickedSignature OnThirstTicked;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="NutritionComponent")
	FOnStarveSignature OnStarve;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="NutritionComponent")
	FOnDehydrateSignature OnDehydrate;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentHunger, EditAnywhere, BlueprintReadWrite, Category="NutritionComponent")
	int32 CurrentHunger = 100;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentThirst, EditAnywhere, BlueprintReadWrite, Category="NutritionComponent")
	int32 CurrentThirst = 100;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="NutritionComponent")
	float HungerTickRate = 25.f;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="NutritionComponent")
	float ThirstTickRate = 20.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="NutritionComponent")
	FTimerHandle HungerTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="NutritionComponent")
	FTimerHandle ThirstTimerHandle;

	UFUNCTION(Server, Reliable, Category="NutritionComponent")
	void Server_SetHunger(int32 NewValue);

	UFUNCTION(Server, Reliable, Category="NutritionComponent")
	void Server_SetThirst(int32 NewValue);

	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void TickHunger();

	UFUNCTION()
	void TickThirst();

	UFUNCTION()
	void OnRep_CurrentHunger();

	UFUNCTION()
	void OnRep_CurrentThirst();
	
};
