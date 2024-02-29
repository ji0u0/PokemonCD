// Fill out your copyright notice in the Description page of Project Settings.


#include "PokemonCDGameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Online/OnlineSessionNames.h"

UPokemonCDGameInstance::UPokemonCDGameInstance()
{
	PlayerID = "tmp";
}

void UPokemonCDGameInstance::Init()
{
	Super::Init();

    //Get IOnlineSubsystem class that has the online session functionality
    IOnlineSubsystem* IOnlineSubsystem = IOnlineSubsystem::Get();

    //if subsystem is not a null
    if (IOnlineSubsystem) {
        SessionInterface = IOnlineSubsystem->GetSessionInterface();
        if (SessionInterface) {
            //Bind function
            SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UPokemonCDGameInstance::OnCreateSessionComplete);
            SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UPokemonCDGameInstance::OnFindSessionComplete);
            SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UPokemonCDGameInstance::OnJoinSessionComplete);
        }
    }

#pragma region Debug Platform Name: NULL or Steam
    //Log connected platform
    FString PlatformName = IOnlineSubsystem->GetSubsystemName().ToString();
    UE_LOG(LogTemp, Warning, TEXT("%s"), *PlatformName);
#pragma endregion
}

void UPokemonCDGameInstance::CreateMySession(FString InRoomName, int32 InPlayerCount)
{
    if (SessionInterface) {
        //Create a session information
        FOnlineSessionSettings SessionSettings;

        SessionSettings.bAllowInvites = false;
        SessionSettings.bAllowJoinInProgress = true;            //allow users to join while session is in progress
        //???
        SessionSettings.bAllowJoinViaPresence = true;
        //making it public
        SessionSettings.bShouldAdvertise = true;
        SessionSettings.bIsDedicated = false;

        //if the online subsystem type is NULL do lan matching, if it's STEAM then do server matching
        SessionSettings.bIsLANMatch = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL";
        //max number of clients that can connect
        SessionSettings.NumPublicConnections = InPlayerCount;

        SessionSettings.Set(FName("KEY_RoomName"), InRoomName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

        //create session
        SessionInterface->CreateSession(0, PlayerID, SessionSettings);

        UE_LOG(LogTemp, Warning, TEXT("Trying to Create Session"));
    }
}

void UPokemonCDGameInstance::OnCreateSessionComplete(FName InSessionName, bool bIsSuccess)
{
    FString Result;

    if (bIsSuccess) {
        Result = TEXT("Create Session Succeeded");
    }
    else {
        Result = TEXT("Create Session Failed");
    }

    //UE_LOG(LogTemp, Warning, TEXT("%s: %s"), Result, InSessionName.ToString());

    //if session is successfully created, move all players connected to the session to the main map
    if (bIsSuccess) {
        //note that Game/ refers to Content Folder
        //[Map directory] ? Listen
        GetWorld()->ServerTravel("/Game/Maps/LV_LobyMap.LV_LobyMap?Listen");

    }
}



void UPokemonCDGameInstance::FindMySession()
{
    //create a query for finding a session; FOnlineSessionSearch is a pointer in Native c++ not unreal
    SessionSearch = MakeShareable(new FOnlineSessionSearch());

    //checking if lan connection; true if subsystem name is null
    SessionSearch->bIsLanQuery = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL";
    //number of sessions to be found
    SessionSearch->MaxSearchResults = 30;
    //Finds specific room by a key; Basically a search filter functionality
    //sessionSearch->QuerySettings.Set(FName("KEY_RoomName"), INSERTROOMNAME, EOnlineComparisonOp::GreaterThanEquals);

    //searching by prseence
    SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

    //Find session using the created query; casting the sessionSearch from TSharedPtr to ToSharedRef
    SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
}

void UPokemonCDGameInstance::OnFindSessionComplete(bool bWasSuccessful)
{
    if (bWasSuccessful) {
        //get array of search results
        TArray<FOnlineSessionSearchResult> SearchResults = SessionSearch->SearchResults;

        UE_LOG(LogTemp, Warning, TEXT("UServerGameInstance::OnFindSessionComplete - Session Count: %d"), SearchResults.Num());

        for (int32 i = 0; i < SearchResults.Num(); i++) {

            FSessionInfo SearchedSessionInfo;

            FString RoomName;
            SearchResults[i].Session.SessionSettings.Get(FName("KEY_RoomName"), RoomName);

            SearchedSessionInfo.RoomSessionName = RoomName;

            //total number of connections: available and taken
            SearchedSessionInfo.MaxPlayerCount = SearchResults[i].Session.SessionSettings.NumPublicConnections;

            //open connections means free, not taken, available connections; maxplayers - open connections = # of connected players
            SearchedSessionInfo.CurrentPlayerCount = SearchedSessionInfo.MaxPlayerCount - SearchResults[i].Session.NumOpenPublicConnections;

            //ping in milliseconds
            SearchedSessionInfo.PingNumber = SearchResults[i].PingInMs;

            //slot index
            SearchedSessionInfo.SlotIndex = i;

            //sending to login widget the necessary information to create a child slot widget 
            SearchResultDelegate.Broadcast(SearchedSessionInfo);
        }
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("Failed to find sessions..."));
    }

    SearchFinishedDelegate.Broadcast();
}

void UPokemonCDGameInstance::JoinMySession(int32 InSessionIndex)
{
    //select session from list of search results with index 
    FOnlineSessionSearchResult SelectedSession = SessionSearch->SearchResults[InSessionIndex];

    //using the sessionID that was made in the login widget, join session
    SessionInterface->JoinSession(0, PlayerID, SelectedSession);
}

void UPokemonCDGameInstance::OnJoinSessionComplete(FName InSessionName, EOnJoinSessionCompleteResult::Type InJoinResult)
{
    //if succeeded in joining, move to coinciding level of the IP Address
    if (InJoinResult == EOnJoinSessionCompleteResult::Success) {

        //get the IP address with session name
        FString JoinAddress;
        SessionInterface->GetResolvedConnectString(InSessionName, JoinAddress);

        //UE_LOG(LogTemp, Warning, TEXT("Join Address: %s"), JoinAddress);

        if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController()) {
            PlayerController->ClientTravel(JoinAddress, ETravelType::TRAVEL_Absolute);
        }
    }
}
