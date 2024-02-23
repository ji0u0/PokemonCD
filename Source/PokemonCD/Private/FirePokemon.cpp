// Fill out your copyright notice in the Description page of Project Settings.


#include "FirePokemon.h"

#include "Enemy.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

// Sets default values
AFirePokemon::AFirePokemon()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCopomponent"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	SkillSpawnPos = CreateDefaultSubobject<UArrowComponent>(TEXT("SkillSpawnPos"));
	
	SetRootComponent(BoxComponent);
	MeshComponent->SetupAttachment(RootComponent);
	SkillSpawnPos->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void AFirePokemon::BeginPlay()
{
	FindActor();
	

}

// Called every frame
void AFirePokemon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFirePokemon::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AFirePokemon::FindActor()
{
	TArray<AActor*> ActorsToFind;
	if(GetWorld())
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), ActorsToFind);
	}
	
	for(AActor* target : ActorsToFind)
	{
		if(target)
		{
			Enemy = Cast<AEnemy>(target);
		}
	}
}

void AFirePokemon::SpawnParticle()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SkillParticle, Enemy->GetActorLocation());
}





