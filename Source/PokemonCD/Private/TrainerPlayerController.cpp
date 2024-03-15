// Fill out your copyright notice in the Description page of Project Settings.


#include "TrainerPlayerController.h"

#include "Trainer.h"
#include "Net/UnrealNetwork.h"

void ATrainerPlayerController::SetPokemon(EPokemonList Selected)
{
	Pokemon = Selected;
}

void ATrainerPlayerController::UseSkill()
{
}

void ATrainerPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATrainerPlayerController, Pokemon);
}
