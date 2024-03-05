// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PokemonGameInstanceSubSystem.generated.h"


/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnCreateSessionComplete, bool, bWasSuccesssful);
DECLARE_MULTICAST_DELEGATE_TwoParams(FMultiplayerOnFindSessionComplete, const TArray<FOnlineSessionSearchResult>& SessionResults, bool bwasSuccessful);
DECLARE_MULTICAST_DELEGATE_OneParam(FMultiplayerOnJoinSessionComplete, EOnJoinSessionCompleteResult::Type Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnStartSessionComplete, bool, bWasSuccessful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnDestroySessionComplete, bool, bWasSuccessful);


UCLASS()
class POKEMONCD_API UPokemonGameInstanceSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPokemonGameInstanceSubSystem();

	// ----------------------------------------------------------------
	// To handle session functionality. The Menu class will call these 
	// ----------------------------------------------------------------
	void CreateSession(int32 NumPublicConnections, FString MatchType);
	void FindSession(int32 MaxSearchResults);
	void JoinSession(const FOnlineSessionSearchResult& SessionResult);
	void StartSession();
	void DestroySession();


	//-------------------------------------------------------------
	// Our own custom delegate for the Menu class to bind callbacks
	//-------------------------------------------------------------
	FMultiplayerOnCreateSessionComplete MultiplayerOnCreateSessionComplete;
	FMultiplayerOnFindSessionComplete MultiplayerOnFindSessionComplete;
	FMultiplayerOnJoinSessionComplete MultiplayerOnJoinSessionComplete;
	FMultiplayerOnStartSessionComplete MultiplayerOnStartSessionComplete;
	FMultiplayerOnDestroySessionComplete MultiplayerOnDestroySessionComplete;

protected:
	// ----------------------------------------------------------------------------------------------
	// Internal Callbacks for the delegate we'll add to the Online Session Interface delegate list.
	// These don't need to be called outside this class. 
	//-----------------------------------------------------------------------------------------------
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnFindSessionComplete(bool bWasSuccessful);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	void OnStartSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);


private:
	IOnlineSessionPtr SessionInterface;
	TSharedPtr<FOnlineSessionSettings>	LastSessionSettings;
	TSharedPtr<FOnlineSessionSearch>	LastSessionSearch;

	bool	bCreateSessionOnDestroy{ false };
	int32	LastNumPublicConnections =0;
	FString LastMatchType;

	// ------------------------------------------------------------------------
	// To add to the Onlie Session Interface delegate list.
	// We'll bind our MultiplayersessionSubsystem internal callbacks to these.
	// ------------------------------------------------------------------------
	FOnCreateSessionCompleteDelegate	CreateSessionCompleteDelegate;
	FDelegateHandle						CreateSessionCompleteDelegateHandle;
	FOnFindSessionsCompleteDelegate		FindSessionCompleteDelegate;
	FDelegateHandle						FindSessionCompleteDelegateHandle;
	FOnJoinSessionCompleteDelegate		JoinSessionCompleteDelegate;
	FDelegateHandle						JoinSessionCompleteDelegateHandle;
	FOnStartSessionCompleteDelegate		StartSessionCompleteDelegate;
	FDelegateHandle						StartSessionCompleteDelegateHandle;
	FOnDestroySessionCompleteDelegate	DestroySessionCompleteDelegate;
	FDelegateHandle						DestroySessionCompleteDelegateHandle;
};
