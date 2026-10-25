#include "RomeroGameInstance.h"

#include "Engine/World.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"

void URomeroGameInstance::HostSession(TSoftObjectPtr<UWorld> Level, const FString &ServerName, bool IsDedicatedServer, int32 MaxPlayers)
{
    if (Level.IsNull())
    {
        OnHostSessionFailure.Broadcast(TEXT("No map was selected."));
        return;
    }

    if (MaxPlayers < 1)
    {
        OnHostSessionFailure.Broadcast(TEXT("MaxPlayers must be at least 1."));
        return;
    }

    IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();

    if (!Subsystem)
    {
        OnHostSessionFailure.Broadcast(TEXT("No Online Subsystem is available."));
        return;
    }

    SessionInterface = Subsystem->GetSessionInterface();

    if (!SessionInterface.IsValid())
    {
        OnHostSessionFailure.Broadcast(TEXT("The session interface is unavailable."));
        return;
    }

    if (SessionInterface->GetNamedSession(NAME_GameSession))
    {
        OnHostSessionFailure.Broadcast(TEXT("A session already exists."));
        return;
    }

    PendingLevel = Level;
    bPendingDedicatedServer = IsDedicatedServer;

    FOnlineSessionSettings Settings;

    Settings.NumPublicConnections = MaxPlayers;
    Settings.NumPrivateConnections = 0;

    Settings.bShouldAdvertise = true;
    Settings.bAllowJoinInProgress = true;

    Settings.bIsLANMatch = Subsystem->GetSubsystemName() == FName("NULL");

	Settings.Set(FName("SERVER_NAME"), ServerName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
    Settings.Set(FName("MAP_NAME"), Level.GetAssetName(), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

    Settings.Set(FName("SERVER_TYPE"), 
    	FString(IsDedicatedServer ? FString(TEXT("Dedicated")) : FString(TEXT("Listen"))), 
    	EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

    CreateSessionCompleteHandle = SessionInterface->AddOnCreateSessionCompleteDelegate_Handle(
            FOnCreateSessionCompleteDelegate::CreateUObject(
                this,
                &URomeroGameInstance::HandleCreateSessionComplete
                ));

    const bool bStarted = SessionInterface->CreateSession(0, NAME_GameSession, Settings);

    if (!bStarted)
    {
        SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteHandle);

        CreateSessionCompleteHandle.Reset();

        OnHostSessionFailure.Broadcast(TEXT("The session creation request could not be started."));
    }
}

void URomeroGameInstance::HandleCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
    if (SessionInterface.IsValid())
    {
        SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteHandle);
    }

    CreateSessionCompleteHandle.Reset();

    if (!bWasSuccessful)
    {
        OnHostSessionFailure.Broadcast(TEXT("The Online Subsystem failed to create the session."));
        return;
    }

    OnHostSessionSuccess.Broadcast();

    if (UWorld* World = GetWorld())
    {
        const FString MapPath = PendingLevel.ToSoftObjectPath().GetLongPackageName();

        if (MapPath.IsEmpty())
        {
            OnHostSessionFailure.Broadcast(TEXT("The selected map has no valid package path."));
            return;
        }

        if (!bPendingDedicatedServer)
        {
            World->ServerTravel(MapPath + TEXT("?listen"));
        }
        else
        {            
            World->ServerTravel(MapPath);
        }
    }
}