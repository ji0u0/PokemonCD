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

	class ATrainerPlayerController* pc;
	class ATrainer* pp;
public:
	class ATrainerPlayerController* pc;
	class ATrainer* pp;

	UPROPERTY(Replicated)
	bool AuthoritySelectPokemon = false;

	UPROPERTY(Replicated)
	bool AutonomousSelectPokemon = false;

	UPROPERTY(EditAnywhere, Replicated)
	bool AuthoritySelectSkill = false;

	UPROPERTY(EditAnywhere, Replicated)
	bool AutonomousSelectSkill = false;

	UFUNCTION()
	void SelectedPokemon();

	void SelectSkill();
	void BattlePhase();
	void Test();

	EGameState State;

	void SetState(EGameState Next);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
