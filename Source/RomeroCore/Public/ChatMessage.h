#pragma once

#include "CoreMinimal.h"

#include "ChatMessage.generated.h"

USTRUCT(Blueprintable)
struct FChatMessage
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Text Chat")
	FString SenderName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Text Chat")
	FString Message;
};