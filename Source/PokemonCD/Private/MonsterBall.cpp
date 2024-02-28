// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterBall.h"

#include "Components/SphereComponent.h"

// Sets default values
AMonsterBall::AMonsterBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MonsterBall = CreateDefaultSubobject<USphereComponent>(TEXT("MonsterBall"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));

	SetRootComponent(MonsterBall);
	MeshComponent->SetupAttachment(RootComponent);
	MonsterBall->SetSimulatePhysics(true);

}

// Called when the game starts or when spawned
void AMonsterBall::BeginPlay()
{
	Super::BeginPlay();
	Throwed();
	
}

// Called every frame
void AMonsterBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}

void AMonsterBall::Throwed()
{
	FVector Dir = this->GetActorForwardVector() * MonsterBall->GetMass() * ThrowedPower;
	MonsterBall->AddImpulse(Dir);
}

