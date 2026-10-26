#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WheeledVehiclePawn.h"
#include "Components/TextRenderComponent.h"

#include "RomeroPlayerController.h"
#include "RomeroPlayer.h"

#include "Interactable.h"
#include "Damageable.h"

#include "RomeroVehicle.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerEnterVehicleSignature, AController*, Controller);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerExitVehicleSignature, AController*, Controller);

UCLASS()
class ARomeroVehicle : public AWheeledVehiclePawn, public IInteractable, public IDamageable
{
	GENERATED_BODY()

public:

	ARomeroVehicle();

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Multiplayer")
	FOnPlayerEnterVehicleSignature OnPlayerEnterVehicle;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Multiplayer")
	FOnPlayerExitVehicleSignature OnPlayerExitVehicle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UTextRenderComponent> PlayerNameText;

	UPROPERTY(ReplicatedUsing = OnRep_OwningPlayerPawn, EditAnywhere, BlueprintReadWrite, Category="Multiplayer")
	TObjectPtr<ARomeroPlayer> OwningPlayerPawn;

	UFUNCTION(Server, Reliable, BlueprintCallable, Category="Multiplayer")
	void Server_EnterVehicle(ARomeroPlayer* Player);

	UFUNCTION(Server, Reliable, BlueprintCallable, Category="Multiplayer")
	void Server_ExitVehicle();

private:

	UFUNCTION()
	void OnRep_OwningPlayerPawn();
	
};
