// Fill out your copyright notice in the Description page of Project Settings.


#include "PokemonGameState.h"


APokemonGameState::APokemonGameState()
{

}


void APokemonGameState::BeginPlay()
{
	Super::BeginPlay();
	SetState(EGameState::SELECTED_POKEMON);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("SELECTED_POKEMON"));
}



void APokemonGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	switch (State)
	{
	case EGameState::SELECTED_POKEMON:	SelectedPokemon();
	case EGameState::SELECT_SKILL:		SelectSkill();		break;
	case EGameState::BATTLE_PHASE:		BattlePhase();		break;
	}
}


void APokemonGameState::SelectedPokemon()
{
	if (AuthoritySelectPokemon == true)
		UE_LOG(LogTemp, Warning, TEXT("%s"), AuthoritySelectPokemon);


	if (AutonomousSelectPokemon == true)
		UE_LOG(LogTemp, Warning, TEXT("%s"), AutonomousSelectPokemon);

	if (AuthoritySelectPokemon == true && AutonomousSelectPokemon == true)
	{

		SetState(EGameState::SELECT_SKILL);
	}
}

void APokemonGameState::SelectSkill()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("SelectPokemonComplete"));
	if (AuthoritySelectSkill == true && AutonomousSelectSkill == true)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("SelectSkillComplete"));
		SetState(EGameState::BATTLE_PHASE);
	}
}



void APokemonGameState::BattlePhase()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Is BattlePhase"));
}

void APokemonGameState::SetState(EGameState Next)
{
	State = Next;
}
