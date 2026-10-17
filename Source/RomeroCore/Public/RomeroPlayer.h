#pragma once

#include "CoreMinimal.h"
#include "RomeroCharacter.h"

#include "Components/StaticMeshComponent.h"
#include "Inventory/InventoryComponent.h"
#include "Weapon/WeaponComponent.h"

#include "RomeroPlayer.generated.h"

UCLASS()
class ARomeroPlayer : public ARomeroCharacter
{
	GENERATED_BODY()

public:

	ARomeroPlayer();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UInventoryComponent> InventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UWeaponComponent> WeaponComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UStaticMeshComponent> HeldWeapon;

	UFUNCTION(BlueprintCallable, Category="Weapon")
	void HandleWeaponChanged(UWeapon* weapon);

protected:

	virtual void PostInitializeComponents() override;
	
};