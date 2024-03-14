// Fill out your copyright notice in the Description page of Project Settings.


#include "TrainerPlayerController.h"

#include "Trainer.h"

void ATrainerPlayerController::SetPokemon(_EPokemonList Selected)
{
	Pokemon = Selected;
}

void ATrainerPlayerController::UseSkill()
{
	auto MyPawn = GetPawn();
	ATrainer* Trainer = Cast<ATrainer>(MyPawn);
	Trainer->ServerSpawnPokemon();
}
