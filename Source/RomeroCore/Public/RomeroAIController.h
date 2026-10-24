#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/PawnSensingComponent.h"
#include "GameFramework/Pawn.h"

#include "RomeroAIController.generated.h"

UCLASS(Blueprintable, BlueprintType)
class ARomeroAIController : public AAIController
{
	GENERATED_BODY()

public:

	ARomeroAIController();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UPawnSensingComponent> PawnSensingComponent;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="AI")
	TObjectPtr<APawn> Target;
	
};
