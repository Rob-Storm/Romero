#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "FindSessionsCallbackProxy.h"
#include "OnlineSessionSettings.h"

#include "RomeroGameInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHostSessionSuccess);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHostSessionFailure, FString, ErrorMessage);

USTRUCT(BlueprintType)
struct FServerSessionInfo
{
    GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, Category = "Session")
    FString ServerName;

    UPROPERTY(BlueprintReadOnly, Category = "Session")
    FString MapName;

    UPROPERTY(BlueprintReadOnly, Category = "Session")
    FString ServerType;
};


UCLASS()
class URomeroGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, Category = "Multiplayer")
	FOnHostSessionSuccess OnHostSessionSuccess;

	UPROPERTY(BlueprintAssignable, Category = "Multiplayer")
	FOnHostSessionFailure OnHostSessionFailure;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Multiplayer")
	FString PlayerName = TEXT("ragamuffin");

	UFUNCTION(BlueprintCallable, Category="Multiplayer")
	void HostSession(TSoftObjectPtr<UWorld> Level, const FString &ServerName, bool IsDedicatedServer, int32 MaxPlayers);

	UFUNCTION(BlueprintPure, Category="Multiplayer", DisplayName="Get Session Info")
	FServerSessionInfo K2_GetSessionInfo(const FBlueprintSessionResult &SearchResult) const
	{
		return GetSessionInfo(SearchResult.OnlineResult);
	}

	FServerSessionInfo GetSessionInfo(const FOnlineSessionSearchResult& SearchResult) const
	{
    	FServerSessionInfo Info;

	    const FOnlineSessionSettings& Settings = SearchResult.Session.SessionSettings;

	    Settings.Get(FName("SERVER_NAME"), Info.ServerName);
    	Settings.Get(FName("MAP_NAME"), Info.MapName);
    	Settings.Get(FName("SERVER_TYPE"), Info.ServerType);

    	return Info;
	}

private:
    IOnlineSessionPtr SessionInterface;

    FDelegateHandle CreateSessionCompleteHandle;

    TSoftObjectPtr<UWorld> PendingLevel;
    bool bPendingDedicatedServer = false;

    void HandleCreateSessionComplete(FName SessionName, bool bWasSuccessful);
};