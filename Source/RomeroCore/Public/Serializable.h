#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "Serializable.generated.h"

UINTERFACE()
class ROMEROCORE_API USerializeable : public UInterface
{
	GENERATED_BODY()
};

class ROMEROCORE_API ISerializeable
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, Category="Serialization")
	void OnActorLoaded();
	
};
