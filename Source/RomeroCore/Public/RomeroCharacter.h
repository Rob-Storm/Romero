#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Damageable.h"
#include "Health/HealthComponent.h"

#include "RomeroCharacter.generated.h"

UCLASS(Blueprintable, BlueprintType)
class ARomeroCharacter : public ACharacter, public IDamageable
{
	GENERATED_BODY()

public:

	ARomeroCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UHealthComponent> HealthComponent;

	virtual void Damage_Implementation(class ARomeroPlayerController* CallingController, class UWeaponData* Weapon) override;

protected:

	virtual void PostInitializeComponents() override;

private:

	UFUNCTION()
	void HandleHealthChanged(int32 CurrentHealth);

	UFUNCTION()
	void HandleKilled();
	
};