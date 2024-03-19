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

DECLARE_DELEGATE(FOnMyPokemonChooseComplete)
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
	class ATrainerPlayerController* pc;
	class ATrainer* pp;

	UPROPERTY(Replicated)
	bool bAuthoritySelectPokemon = false;

	UPROPERTY(Replicated)
	bool bAutonomousSelectPokemon = false;

	UPROPERTY(EditAnywhere)
	bool AuthoritySelectSkill = false;

	UPROPERTY(EditAnywhere)
	bool AutonomousSelectSkill = false;

	UFUNCTION()
	void SelectedPokemon();

	UFUNCTION()
	void ShowSkillWidget();

	void SelectSkill();
	void BattlePhase();
	void Test();

	FOnMyPokemonChooseComplete OnSpawnPokemonDelegate;

	EGameState State;

	void SetState(EGameState Next);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
