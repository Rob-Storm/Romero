#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Weapon/Weapon.h"

#include "WeaponComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponChangedSignature, UWeapon*, Weapon);

UCLASS(Blueprintable, BlueprintType)
class UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UWeaponComponent();

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Weapon")
	FOnWeaponChangedSignature OnWeaponChanged;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentWeapon, EditAnywhere, BlueprintReadWrite, Category="Weapon")
	TObjectPtr<UWeapon> CurrentWeapon;

	UFUNCTION(Server, Reliable, BlueprintCallable, Category="Weapon")
	void Server_SetWeapon(UWeapon* NewWeapon);

	UFUNCTION(Server, Reliable, BlueprintCallable, Category="Weapon")
	void Server_WeaponTrace();

	UFUNCTION(Server, Reliable, BlueprintCallable, Category="Weapon")
	void Server_Shoot();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:

	UFUNCTION()
	void OnRep_CurrentWeapon();
	
};