// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystem.h"
#include "Engine/GameInstance.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "PokemonCDGameInstance.generated.h"

/**
 * 
 */

USTRUCT()
struct FSessionInfo
{
    GENERATED_BODY()

    FString RoomSessionName;
    int32 CurrentPlayerCount;
    int32 MaxPlayerCount;
    int32 PingNumber;
    int32 SlotIndex;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSearchResult, FSessionInfo, sessionInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSearchFinished);



UCLASS()
class POKEMONCD_API UPokemonCDGameInstance : public UGameInstance
{
	GENERATED_BODY()
    
	UPokemonCDGameInstance();
public:
	virtual void Init() override;

    
    IOnlineSessionPtr SessionInterface;

    TSharedPtr<FOnlineSessionSearch> SessionSearch;

    //declare delegate for Searching sessions
    FOnSearchResult SearchResultDelegate;
    FOnSearchFinished SearchFinishedDelegate;

    FName PlayerID;

#pragma region Create Session
    //rename later
    void CreateMySession(FString InRoomName, int32 InPlayerCount);

    UFUNCTION()
    void OnCreateSessionComplete(FName InSessionName, bool bIsSuccess);
#pragma endregion


#pragma region Find and Join Sessions
    //Finds created sessions
    void FindMySession();
    UFUNCTION()
    void OnFindSessionComplete(bool bWasSuccessful);

    void JoinMySession(int32 InSessionIndex);

    //Delegate for Joining Sessions
    FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;

    void OnJoinSessionComplete(FName InSessionName, EOnJoinSessionCompleteResult::Type InJoinResult);
#pragma endregion

};
