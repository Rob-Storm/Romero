#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "Interactable.generated.h"

UINTERFACE()
class ROMEROCORE_API UInteractable : public UInterface
{
	GENERATED_BODY()
};

class ROMEROCORE_API IInteractable
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interactable")
	void Interact(class ARomeroPlayerController* CallingController);
	virtual void Interact_Implementation(class ARomeroPlayerController* CallingController);
	
};