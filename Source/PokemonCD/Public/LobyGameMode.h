// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PokemonCDGameInstance.h"
#include "GameFramework/GameMode.h"
#include "LobyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class POKEMONCD_API ALobyGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ALobyGameMode();
	virtual void BeginPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

	

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> LobbyServerWidgetTemplate;

	UPROPERTY()
	class ULobbyServerWidget* LobbyServerWidget;


protected:
	UPROPERTY()
	class UPokemonCDGameInstance* GameInstance;
};
