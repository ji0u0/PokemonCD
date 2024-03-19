// Fill out your copyright notice in the Description page of Project Settings.


#include "PokemonGameState.h"

#include "PokemonWater.h"
#include "Trainer.h"
#include "WidgetSkill.h"
#include "GameFramework/PlayerState.h"
#include "Net/UnrealNetwork.h"


APokemonGameState::APokemonGameState()
{
	bReplicates = true;
	PrimaryActorTick.bCanEverTick = true;
}


void APokemonGameState::BeginPlay()
{
	Super::BeginPlay();

	pc = Cast<ATrainerPlayerController>(GetWorld()->GetFirstPlayerController());
	UE_LOG(LogTemp, Warning, TEXT("pc: %d"), pc->GetPlayerState<APlayerState>()->GetPlayerId())


	pp = Cast<ATrainer>(pc->GetPawn());

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
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("SELECTED_POKEMON"));

	if (AuthoritySelectPokemon == true)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("AuthoritySelectPokemon : True"));


	if (AutonomousSelectPokemon == true)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("AutonomousSelectPokemon : True"));


	if (AuthoritySelectPokemon == true)
	// if (AuthoritySelectPokemon == true && AutonomousSelectPokemon == true)
	{
		SetState(EGameState::SELECT_SKILL);
		if (pp)
		{
			FTimerHandle handle;
			GetWorldTimerManager().SetTimer(handle, this, &APokemonGameState::ShowSkillWidget, 3.0f, false);
		}
	}
}

void APokemonGameState::ShowSkillWidget()
{
	pp->SkillWidgetCreate();
}

void APokemonGameState::SelectSkill()
{
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

