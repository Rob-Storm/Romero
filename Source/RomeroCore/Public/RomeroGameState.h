#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"

#include "ChatMessage.h"

#include "RomeroGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnChatHistoryChangedSignature);

UCLASS()
class ARomeroGameState : public AGameState
{
	GENERATED_BODY()

public:

	ARomeroGameState();

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Text Chat")
	FOnChatHistoryChangedSignature OnChatHistoryChanged;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game State")
	int32 CurrentHour = 0;

	UPROPERTY(ReplicatedUsing = OnRep_ChatHistory, EditAnywhere, BlueprintReadWrite, Category="Text Chat")
	TArray<FChatMessage> ChatHistory;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Text Chat")
	void ChatHistoryChanged();

	UFUNCTION(Server, Reliable, BlueprintCallable, Category="Text Chat")
	void Server_SendChatMessage(const FChatMessage& Message);

private:

	UFUNCTION()
	void OnRep_ChatHistory();
	
};
