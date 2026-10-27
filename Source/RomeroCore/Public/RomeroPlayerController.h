#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "Blueprint/UserWidget.h"

#include "InputMappingContext.h"

#include "OnlineSubsystem.h"
#include "VoiceModule.h"
#include "Interfaces/VoiceInterface.h"

#include "ChatMessage.h"

#include "RomeroPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnVehicleModeChangedSignature);

UCLASS()
class ARomeroPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Vehicles")
	FOnVehicleModeChangedSignature OnVehicleModeChanged;

	UPROPERTY(EditAnywhere, Category="Input")
	TSoftObjectPtr<UInputMappingContext> FirstPersonMapping;

	UPROPERTY(EditAnywhere, Category="Input")
	TSoftObjectPtr<UInputMappingContext> CarMapping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pawn")
	FTransform UnpossessTransform;

	virtual void BeginPlay() override;
	virtual void BeginPlayingState() override;

	virtual void OnUnPossess() override;

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

	UFUNCTION(Client, Reliable, BlueprintCallable, Category="Vehicles")
	void EnterCar();

	UFUNCTION(Client, Reliable, BlueprintCallable, Category="Vehicles")
	void ExitCar();
};