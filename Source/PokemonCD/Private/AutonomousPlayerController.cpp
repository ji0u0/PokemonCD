// Fill out your copyright notice in the Description page of Project Settings.


#include "AutonomousPlayerController.h"

#include "PokemonGameMode.h"
#include "Kismet/GameplayStatics.h"


void AAutonomousPlayerController::BeginPlay()
{
	Super::BeginPlay();

	GameMode = GetWorld()->GetAuthGameMode<APokemonGameMode>();
}

void AAutonomousPlayerController::CheckRoleAndPossess()
{
	if(GameMode)
	{
		int32 PlayerNum = UGameplayStatics::GetNumPlayerStates(this);
	}
}
