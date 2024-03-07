// Fill out your copyright notice in the Description page of Project Settings.


#include "TestGameMode.h"

#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"


ATestGameMode::ATestGameMode()
{
    SetValue();
}

void ATestGameMode::BeginPlay()
{
    Super::BeginPlay();

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

    SpawnPlayerCharacter();
}

void ATestGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    UE_LOG(LogTemp, Warning, TEXT("PostLogin "));
    UE_LOG(LogTemp, Warning, TEXT("%s logged in "), *NewPlayer->GetName());

    PossessPlayerCharacter(NewPlayer);
}

void ATestGameMode::SetValue()
{
    PlayerScale = FVector(1, 1, 1);

    AuthoritySpawnLoc = FVector(0, 0, 0);
    AuthoritySpawnRotate = FQuat(0, 0, 0, 1);

    AuthorityTransform.SetLocation(AuthoritySpawnLoc);
    AuthorityTransform.SetRotation(AuthoritySpawnRotate);
    AuthorityTransform.SetScale3D(PlayerScale);

    AutonomousProxySpawnLoc = FVector(1000, 0, 0);
    AutonomousProxySpawnRotate = FQuat(0, 0, 180, 1);


    AutonomousProxyTransform.SetLocation(AutonomousProxySpawnLoc);
    AutonomousProxyTransform.SetRotation(AutonomousProxySpawnRotate);
    AutonomousProxyTransform.SetScale3D(PlayerScale);

}



void ATestGameMode::SpawnPlayerCharacter()
{
    //Spawn Authority and Autonomous Character
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    SpawnParams.bNoFail = true;

    Authority = GetWorld()->SpawnActor<ATestLobyPlayer>(LobbyPlayerTemplate, AuthorityTransform, SpawnParams);


    Autonomous = GetWorld()->SpawnActor<ATestLobyPlayer>(LobbyPlayerTemplate, AutonomousProxyTransform, SpawnParams);
    
}

void ATestGameMode::PossessPlayerCharacter(APlayerController* NewPlayer)
{
    GetWorld()->GetFirstPlayerController()->Possess(Authority);
    NewPlayer->Possess(Autonomous);
}
