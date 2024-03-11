// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "PokemonGameState.generated.h"

enum class EGameState
{
	SELECTED_POKEMON,
	SELECT_SKILL,
	BATTLE_PHASE
};

/**
 * 
 */
UCLASS()
class POKEMONCD_API APokemonGameState : public AGameState
{
	GENERATED_BODY()

	APokemonGameState();
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere)
	bool AuthoritySelectPokemon = false;
	UPROPERTY(EditAnywhere)
	bool AutonomousSelectPokemon = false;
	bool AuthoritySelectSkill = false;
	bool AutonomousSelectSkill = false;

	UFUNCTION()
	void SelectedPokemon();

	void SelectSkill();
	void BattlePhase();

	EGameState State;

	void SetState(EGameState Next);
};
