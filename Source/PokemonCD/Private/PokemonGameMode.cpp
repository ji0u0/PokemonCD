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

void APokemonGameMode::StartPlay()
{
	Super::StartPlay();
}

void APokemonGameMode::BeginPlay()
{
	Super::BeginPlay();
	
}

void APokemonGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	
}

void APokemonGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if(NewPlayer->HasAuthority() && NewPlayer->IsLocalPlayerController())
	{
		SpawnAuthority(NewPlayer);
	}
	else
	{
		SpawnAutonomous(NewPlayer);
	}
		

	UE_LOG(LogTemp, Warning, TEXT(" APokemonGameMode::PostLogin - %s logged in "), *NewPlayer->GetName());


	//PossessPlayerCharacter(NewPlayer);
}

//void APokemonGameMode::SpawnPlayerCharacter()
//{
//	//Spawn Authority and Autonomous Character
//	FActorSpawnParameters SpawnParams;
//	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
//	SpawnParams.bNoFail = true;
//
//
//
//	Authority = GetWorld()->SpawnActor<ATrainer>(PlayerTemplate, AuthorityTransform, SpawnParams);
//	if (Authority)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("%s Spawned Authority"), *Authority->GetName());
//	}
//
//	Autonomous = GetWorld()->SpawnActor<ATrainer>(PlayerTemplate, AutonomousProxyTransform, SpawnParams);
//	if (Autonomous)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("%s Spawned Autonomous"), *Autonomous->GetName());
//	}
//}

void APokemonGameMode::SetValue()
{
	PlayerScale = FVector(1.f);

	AuthoritySpawnLoc = FVector(40, 1720, 30);
	AuthoritySpawnRotate = FQuat(0, 0, FMath::RadiansToDegrees(270), 1);

	AuthorityTransform.SetLocation(AuthoritySpawnLoc);
	AuthorityTransform.SetRotation(AuthoritySpawnRotate);
	AuthorityTransform.SetScale3D(PlayerScale);

	AutonomousProxySpawnLoc = FVector(40, -990, 30);
	AutonomousProxySpawnRotate = FQuat(0, 0, 0, 1);


	AutonomousProxyTransform.SetLocation(AutonomousProxySpawnLoc);
	AutonomousProxyTransform.SetRotation(AutonomousProxySpawnRotate);
	AutonomousProxyTransform.SetScale3D(PlayerScale);
}

void APokemonGameMode::PossessPlayerCharacter(APlayerController* NewPlayer)
{

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.bNoFail = true;



	Authority = GetWorld()->SpawnActor<ATrainer>(PlayerTemplate, AuthorityTransform, SpawnParams);
	if (Authority)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Spawned Authority"), *Authority->GetName());
	}

	Autonomous = GetWorld()->SpawnActor<ATrainer>(PlayerTemplate, AutonomousProxyTransform, SpawnParams);
	if (Autonomous)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Spawned Autonomous"), *Autonomous->GetName());
	}

	if (NewPlayer->HasAuthority() && NewPlayer->IsLocalPlayerController())
	{
		NewPlayer->Possess(Authority);
		UE_LOG(LogTemp, Warning, TEXT("%s I Possess Authority"), *NewPlayer->GetName());
		
	}
	else if (NewPlayer->HasAuthority() && !NewPlayer->IsLocalPlayerController())
	{
		NewPlayer->Possess(Autonomous);
		UE_LOG(LogTemp, Warning, TEXT("%s I Possess Autonomous"), *NewPlayer->GetName());
		
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

void APokemonGameMode::SpawnAuthority(APlayerController* NewPlayer)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.bNoFail = true;

	Authority = GetWorld()->SpawnActor<ATrainer>(PlayerTemplate, AuthorityTransform, SpawnParams);
	if (Authority)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Spawned Authority"), *Authority->GetName());
	}

	NewPlayer->Possess(Authority);
	NewPlayer->SetRole(ROLE_Authority);
	UE_LOG(LogTemp, Warning, TEXT("%s I Possess Authority"), *NewPlayer->GetName());
}

void APokemonGameMode::SpawnAutonomous(APlayerController* NewPlayer)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.bNoFail = true;

	Autonomous = GetWorld()->SpawnActor<ATrainer>(PlayerTemplate, AutonomousProxyTransform, SpawnParams);
	if (Autonomous)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Spawned Autonomous"), *Autonomous->GetName());
	}

	NewPlayer->Possess(Autonomous);
	NewPlayer->SetRole(ROLE_AutonomousProxy);
	UE_LOG(LogTemp, Warning, TEXT("%s I Possess Autonomous"), *NewPlayer->GetName());
}




