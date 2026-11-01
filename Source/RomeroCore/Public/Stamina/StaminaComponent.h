#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "StaminaComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStaminaChangedSignature, int32, CurrentStamina);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartSprintSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndSpringSignature);

UCLASS()
class UStaminaComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UStaminaComponent();

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="StaminaComponent")
	FOnStaminaChangedSignature OnStaminaChanged;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="StaminaComponent")
	FOnStartSprintSignature OnStartSprint;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="StaminaComponent")
	FOnEndSpringSignature OnEndSprint;
	
	UPROPERTY(ReplicatedUsing = OnRep_CurrentStamina, EditAnywhere, BlueprintReadWrite, Category="StaminaComponent")
	int32 CurrentStamina = 100;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="StaminaComponent")
	float RecoverDelay = 5.f;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="StaminaComponent")
	float RecoverRate = 0.25f;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="StaminaComponent")
	float StaminaConsumptionRate = 0.35f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="StaminaComponent")
	FTimerHandle SprintHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="StaminaComponent")
	FTimerHandle RecoverDelayHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="StaminaComponent")
	FTimerHandle RecoverHandle;

	UFUNCTION(Server, Reliable, BlueprintCallable, Category="StaminaComponent")
	void Server_StartSprint();

	UFUNCTION(Server, Reliable, BlueprintCallable, Category="StaminaComponent")
	void Server_EndSprint();

	UFUNCTION(Server, Reliable, BlueprintCallable, Category="StaminaComponent")
	void Server_SetStamina(int32 NewValue);

	UFUNCTION(BlueprintPure, Category="StaminaComponent")
	bool CanSprint() const
	{
		return CurrentStamina > 0;
	}

private:

	UFUNCTION()
	void BeginStaminaRecovery();

	UFUNCTION()
	void TickStaminaUp();

	UFUNCTION()
	void TickStaminaDown();

	UFUNCTION()
	void OnRep_CurrentStamina();
	
};
