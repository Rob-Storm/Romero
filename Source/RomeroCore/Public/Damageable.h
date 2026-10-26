#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "Damageable.generated.h"

UINTERFACE()
class ROMEROCORE_API UDamageable : public UInterface
{
	GENERATED_BODY()
};

class ROMEROCORE_API IDamageable
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Damageable")
	void Damage(class ARomeroPlayerController* CallingController, class UWeaponData* Weapon);
	virtual void Damage_Implementation(class ARomeroPlayerController* CallingController, class UWeaponData* Weapon);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Damageable")
	void Kill(class ARomeroPlayerController* CallingController);
	virtual void Kill_Implementation(class ARomeroPlayerController* CallingController);
};
