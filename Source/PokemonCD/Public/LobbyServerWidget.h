// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyServerWidget.generated.h"

/**
 * 
 */
UCLASS()
class POKEMONCD_API ULobbyServerWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* CreateSessionButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* JoinSessionButton;

public:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* BattleStartButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* WatingPlayerText;

protected:
	UFUNCTION()
	void CreateSession();
	UFUNCTION()
	void JoinSession();
	UFUNCTION()
	void OpenBattleLevel();

	void UpdatePlayerCount(int32 PlayerCount);


	UPROPERTY()
	class UPokemonGameInstanceSubSystem* PokemonGameInstanceSubSystem;
	UPROPERTY()
	class ALobyGameMode* GameMode;
};
