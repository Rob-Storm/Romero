#pragma once

#include "CoreMinimal.h"
#include "RomeroCharacter.h"

#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"

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
	TObjectPtr<UTextRenderComponent> PlayerNameText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UStaticMeshComponent> HeldWeapon;

	UPROPERTY(ReplicatedUsing = OnRep_SetPawnName, EditAnywhere, BlueprintReadWrite, Category="RomeroCore")
	FString PawnName;

	UFUNCTION(BlueprintCallable, Category="Weapon")
	void HandleWeaponChanged(UWeapon* Weapon);

	UFUNCTION(Server, Reliable, BlueprintCallable, Category="RomeroCore")
	void Server_SetPlayerText();

protected:

	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

private:

	UFUNCTION()
	void OnRep_SetPawnName();
	
};