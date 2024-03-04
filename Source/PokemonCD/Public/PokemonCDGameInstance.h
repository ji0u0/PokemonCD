// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	int32 GetNumberPlayers() const { return NumPlayers; }

	void UpdateNumPlayers(int32 NewNumPlayers) { NumPlayers = NewNumPlayers; }

	IOnlineSessionPtr SessionInterface;

	void CreateSession();
	void JoinSession();

protected:
	int32 NumPlayers;
};
