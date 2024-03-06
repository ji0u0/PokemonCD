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


	void OpenLobby();
	void CallOpenLevel(const FString& Address);
	void ServerTravel();
};
