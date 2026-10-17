#include "RomeroPlayerController.h"
#include "RomeroGameState.h"

#include "Kismet/GameplayStatics.h"

void ARomeroPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

// The player state is not valid at BeginPlay so we must use this function instead
void ARomeroPlayerController::BeginPlayingState()
{
	Super::BeginPlayingState();

	/*
	if(IsLocalController())
	{
		IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();

		if(OnlineSubsystem)
		{
			VoiceInterface = OnlineSubsystem->GetVoiceInterface();
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("OnlineSubsystem is not valid!"));
		}
	}
	*/

}

void ARomeroPlayerController::BeginVoiceChat()
{
	/*
	if(VoiceInterface.IsValid())
	{
		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Green, TEXT("BeginVoice"));
		VoiceInterface->StartNetworkedVoice(0);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("VoiceInterface is not valid!"));
	}
	*/

	ToggleSpeaking(true);
}

void ARomeroPlayerController::EndVoiceChat()
{
	/*
	if(VoiceInterface.IsValid())
	{
		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Blue, TEXT("EndVoice"));
		VoiceInterface->StopNetworkedVoice(0);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("VoiceInterface is not valid!"));
	}
	*/

	ToggleSpeaking(false);
}

void ARomeroPlayerController::Server_SendChatMessage_Implementation(const FChatMessage& Message)
{
	TObjectPtr<ARomeroGameState> GS = Cast<ARomeroGameState>(UGameplayStatics::GetGameState(this));

	if(!GS)
	{
		return;
	}

	GS->Server_SendChatMessage(Message);
}
