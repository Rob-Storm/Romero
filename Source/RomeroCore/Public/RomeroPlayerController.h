#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "Blueprint/UserWidget.h"

#include "OnlineSubsystem.h"
#include "VoiceModule.h"
#include "Interfaces/VoiceInterface.h"

#include "ChatMessage.h"

#include "RomeroPlayerController.generated.h"

UCLASS()
class ARomeroPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;
	virtual void BeginPlayingState() override;

	IOnlineVoicePtr VoiceInterface;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="UserInterface")
	void FocusWidget(UUserWidget* InWidget, bool ShowCursor = true);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="UserInterface")
	void FocusGame();

	UFUNCTION(BlueprintCallable, Category="VoiceChat")
	void BeginVoiceChat();

	UFUNCTION(BlueprintCallable, Category="VoiceChat")
	void EndVoiceChat();

	UFUNCTION(Server, Reliable, BlueprintCallable, Category="Text Chat")
	void Server_SendChatMessage(const FChatMessage& Message);	
};