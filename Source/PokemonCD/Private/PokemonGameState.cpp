// Fill out your copyright notice in the Description page of Project Settings.


#include "PokemonGameState.h"

#include "Trainer.h"
#include "Net/UnrealNetwork.h"


APokemonGameState::APokemonGameState()
{
	bReplicates = true;
	PrimaryActorTick.bCanEverTick = true;
}


void APokemonGameState::BeginPlay()
{
	Super::BeginPlay();
	SetState(EGameState::SELECTED_POKEMON);
	
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
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("SELECTED_POKEMON"));

	if (AuthoritySelectPokemon == true)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("AuthoritySelectPokemon : True"));


	if (AutonomousSelectPokemon == true)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("AutonomousSelectPokemon : True"));


	if (AuthoritySelectPokemon == true)
	//if (AuthoritySelectPokemon == true && AutonomousSelectPokemon == true)
	{
		SetState(EGameState::SELECT_SKILL);
		/*FTimerHandle handle;
		GetWorldTimerManager().SetTimer(handle, []()
		{
			GetWorld()->GetFirstPlayerController()->GetPawn()
		}, 3.f, false);*/
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
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Is BattlePhase"));
}

void APokemonGameState::Test()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("AuthoritySelectPokemon : True"));
}

void APokemonGameState::SetState(EGameState Next)
{
	State = Next;
}

void APokemonGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APokemonGameState, AuthoritySelectPokemon)
	DOREPLIFETIME(APokemonGameState, AutonomousSelectPokemon)
}

