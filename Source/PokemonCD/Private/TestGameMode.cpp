// Fill out your copyright notice in the Description page of Project Settings.


#include "TestGameMode.h"

#include "Kismet/GameplayStatics.h"


ATestGameMode::ATestGameMode()
{
    SetValue();
}

void ATestGameMode::BeginPlay()
{
    Super::BeginPlay();

    SpawnPlayerCharacter();
}


void ATestGameMode::SpawnPlayerCharacter()
{
    //Spawn Authority and Autonomous Character
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    SpawnParams.bNoFail = true;

    ATestLobyPlayer* Authority = GetWorld()->SpawnActor<ATestLobyPlayer>(LobbyPlayerTemplate, AuthorityTransform, SpawnParams);

    //if(Authority){UE_LOG(LogTemp, Warning, TEXT("%s"), Authority != nullptr ? TEXT("spawn") : TEXT("no spawn"))}

    ATestLobyPlayer* Autonomous = GetWorld()->SpawnActor<ATestLobyPlayer>(LobbyPlayerTemplate, AutonomousProxyTransform, SpawnParams);

    //if (Autonomous) { UE_LOG(LogTemp, Warning, TEXT("%s"), Autonomous != nullptr ? TEXT("spawn") : TEXT("no spawn")) }

    //Possess each Character

    if (Authority->GetLocalRole() == ROLE_Authority)
    {
        APlayerController* HostController = GetWorld()->GetFirstPlayerController();
        HostController->Possess(Authority);
    }
    else if (Autonomous->GetLocalRole() == ROLE_AutonomousProxy)
    {
        APlayerController* ClientController = GetWorld()->GetGameInstance()->GetFirstLocalPlayerController();
        if (ClientController)
        {
            ClientController->Possess(Autonomous);
        }
    }
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
    AutonomousProxySpawnRotate = FQuat(0, 0, 0, 1);


    AutonomousProxyTransform.SetLocation(AutonomousProxySpawnLoc);
    AutonomousProxyTransform.SetRotation(AutonomousProxySpawnRotate);
    AutonomousProxyTransform.SetScale3D(PlayerScale);
}

