#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, int32, CurrentHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnKilledSignature);

UCLASS(Blueprintable, BlueprintType)
class UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UHealthComponent();

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Health")
	FOnHealthChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Health")
	FOnKilledSignature OnKilled;

	UPROPERTY(ReplicatedUsing = OnRep_CurentHealth, EditAnywhere, BlueprintReadWrite, Category="Health")
	int32 CurrentHealth = 100;

	UFUNCTION(Server, Reliable, BlueprintCallable, Category="Health")
	void Server_AddHealth(int32 amount);

	UFUNCTION(Server, Reliable, BlueprintCallable, Category="Health")
	void Server_Kill();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


private:

	UFUNCTION()
	void OnRep_CurentHealth();
	
};
