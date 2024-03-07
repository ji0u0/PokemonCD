// Fill out your copyright notice in the Description page of Project Settings.


#include "PokemonGameMode.h"

#include "Trainer.h"
#include "LoadingUI.h"
#include "MainWidget.h"
#include "Blueprint/UserWidget.h"


APokemonGameMode::APokemonGameMode()
{
	bReplicates = true;
	SetValue();
}

void APokemonGameMode::BeginPlay()
{
	Super::BeginPlay();
	//CheckPlayerLogin();
	//SpawnPlayerCharacter();
}

void APokemonGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	switch (State)
	{
	case EGameState::SELECTED_POKEMON:	SelectedPokemon();
	case EGameState::SELECT_SKILL:		SelectSkill();
	case EGameState::BATTLE_PHASE:		BattlePhase();
	}
}

void APokemonGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);


	UE_LOG(LogTemp, Warning, TEXT(" APokemonGameMode::PostLogin - %s logged in "), *NewPlayer->GetName());

	PossessPlayerCharacter(NewPlayer);
	SetState(EGameState::SELECTED_POKEMON);

}

void APokemonGameMode::SpawnPlayerCharacter()
{
	//Spawn Authority and Autonomous Character
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.bNoFail = true;

	Authority = GetWorld()->SpawnActor<ATrainer>(PlayerTemplate, AuthorityTransform, SpawnParams);

	Autonomous = GetWorld()->SpawnActor<ATrainer>(PlayerTemplate, AutonomousProxyTransform, SpawnParams);
}

void APokemonGameMode::SetValue()
{
	PlayerScale = FVector(0.3, 0.3, 0.3);

	AuthoritySpawnLoc = FVector(40, 1720, 20);
	AuthoritySpawnRotate = FQuat(0, 0, 0, 1);

	AuthorityTransform.SetLocation(AuthoritySpawnLoc);
	AuthorityTransform.SetRotation(AuthoritySpawnRotate);
	AuthorityTransform.SetScale3D(PlayerScale);

	AutonomousProxySpawnLoc = FVector(40, -990, 20);
	AutonomousProxySpawnRotate = FQuat(0, 0, 180, 1);


	AutonomousProxyTransform.SetLocation(AutonomousProxySpawnLoc);
	AutonomousProxyTransform.SetRotation(AutonomousProxySpawnRotate);
	AutonomousProxyTransform.SetScale3D(PlayerScale);
}

void APokemonGameMode::PossessPlayerCharacter(APlayerController* NewPlayer)
{
	//GetWorld()->GetFirstPlayerController()->Possess(Authority);

	UE_LOG(LogTemp, Warning, TEXT("%s trying to possess"), *NewPlayer->GetName());

	//Spawn Authority and Autonomous Character
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.bNoFail = true;

	if(NewPlayer->HasAuthority() && NewPlayer->IsLocalController())
	{

		Authority = GetWorld()->SpawnActor<ATrainer>(PlayerTemplate, AuthorityTransform, SpawnParams);

		if(Authority)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s Spawned Authority"), *NewPlayer->GetName());
		}

		UE_LOG(LogTemp, Warning, TEXT("%s trying to possess Authority"), *NewPlayer->GetName());

		NewPlayer->Possess(Authority);
		
	}
	else {

		Autonomous = GetWorld()->SpawnActor<ATrainer>(PlayerTemplate, AutonomousProxyTransform, SpawnParams);

		if (Autonomous)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s Spawned Autonomous"), *NewPlayer->GetName());
		}

		UE_LOG(LogTemp, Warning, TEXT("%s trying to possess Autonomous"), *NewPlayer->GetName());

		NewPlayer->Possess(Autonomous);
		
	}
	
}

void APokemonGameMode::CheckPlayerLogin()
{
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay"))

		for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
		{
			APlayerController* PlayerController = It->Get();
			if (PlayerController)
			{
				UE_LOG(LogTemp, Warning, TEXT("PlayerController logged in: %s"), *PlayerController->GetName());
			}
		}

	UE_LOG(LogTemp, Warning, TEXT("BeginPlay finished"));
}

void APokemonGameMode::SelectedPokemon()
{
	if (AuthoritySelectPokemon && AutonomousSelectPokemon)
		SetState(EGameState::SELECT_SKILL);
}

void APokemonGameMode::SelectSkill()
{
	if (AuthoritySelectSkill && AutonomousSelectSkill)
	{
		UE_LOG(LogTemp, Warning, TEXT("State SelectSkill"));
		SetState(EGameState::BATTLE_PHASE);
	}
}

void APokemonGameMode::BattlePhase()
{

}

void APokemonGameMode::SetState(EGameState Next)
{
	State = Next;
}


