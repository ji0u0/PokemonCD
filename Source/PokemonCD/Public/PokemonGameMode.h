// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PokemonGameMode.generated.h"



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
class POKEMONCD_API APokemonGameMode : public AGameMode
{
	GENERATED_BODY()
	APokemonGameMode();
	virtual void StartPlay() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void PostLogin(APlayerController* NewPlayer) override;

public :

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ATrainer> PlayerTemplate;

	ATrainer* Authority;
	ATrainer* Autonomous;

	TArray<APlayerController*> ControllerArray;

	


	bool AuthoritySelectPokemon = false;
	bool AutonomousSelectPokemon = false;
	bool AuthoritySelectSkill = false;
	bool AutonomousSelectSkill = false;

	//<<<<<<< Updated upstream
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> LoadingUITemplate;

	UPROPERTY()
	class ULoadingUI* LoadingUI;

	// Main Widget
//=======
	// Choose Pokemon Widget
//>>>>>>> Stashed changes
	

	int32 tmp = 0;
private:
	EGameState State;

	void SpawnPlayerCharacter();
	void SetValue();

	void PossessPlayerCharacter(APlayerController* NewPlayer);
	void CheckPlayerLogin();


	void SelectedPokemon();
	void SelectSkill();
	void BattlePhase();

	void SetState(EGameState Next);

	FTransform AuthorityTransform;
	FTransform AutonomousProxyTransform;


	FVector AuthoritySpawnLoc;
	FQuat AuthoritySpawnRotate;

	FVector AutonomousProxySpawnLoc;
	FQuat AutonomousProxySpawnRotate;

	FVector PlayerScale;
};
