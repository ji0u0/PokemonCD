// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSessionSettings.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "PokemonCDGameInstance.generated.h"

/**
 * 
 */

UCLASS()
class POKEMONCD_API UPokemonCDGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPokemonCDGameInstance();
	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;
	FOnFindSessionsCompleteDelegate FindSessionCompleteDelegate;
	FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;

	int32 GetNumberPlayers() const { return NumPlayers; }

	void UpdateNumPlayers(int32 NewNumPlayers) { NumPlayers = NewNumPlayers; }

	IOnlineSessionPtr SessionInterface;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
	
	void CreateSession();
	void JoinSession();

	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnFindSessionComplete(bool bWasSuccessful);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	IOnlineSessionPtr OnlineSessionInterface;

protected:
	int32 NumPlayers = 0;
};
