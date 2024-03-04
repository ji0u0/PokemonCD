// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "LobyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class POKEMONCD_API ALobyGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	virtual  void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> LobbyServerWidgetTemplate;

	UPROPERTY()
	class ULobbyServerWidget* LobbyServerWidget;
};
