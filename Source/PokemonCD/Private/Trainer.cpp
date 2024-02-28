// Fill out your copyright notice in the Description page of Project Settings.


#include "Trainer.h"

#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ATrainer::ATrainer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	ThrowingPosition = CreateDefaultSubobject<UArrowComponent>(TEXT("ThrowingPosition"));

	SetRootComponent(BoxComponent);
	MeshComponent->SetupAttachment(RootComponent);
	ThrowingPosition->SetupAttachment(RootComponent);

	MeshComponent->SetRelativeLocation(FVector(0, 0, 70));
	MeshComponent->SetRelativeScale3D(FVector(0.5, 0.5, 2.0));

	ThrowingPosition->SetRelativeLocation(FVector(50, 0, 130));
}

// Called when the game starts or when spawned
void ATrainer::BeginPlay()
{
	Super::BeginPlay();

	ThrowingMonsterBall();
}

// Called every frame
void ATrainer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATrainer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATrainer::ThrowingMonsterBall()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Walking"));
	FTransform ThrowingTransfrom = ThrowingPosition->GetComponentTransform();
	
	 MonsterBall = GetWorld()->SpawnActor<AMonsterBall>(MonsterBallFactory, ThrowingTransfrom);
	//GetWorld()->GetTimerManager().SetTimer(MonsterBallTimer, this, &ATrainer::SpawnPokemon, 0.5f, false, 0.5f);
}

void ATrainer::SpawnPokemon()
{
	//GetWorld()->SpawnActor<AFirePokemon>(FirePokemon, MonsterBall->GetActorTransform());
	MonsterBall->Destroy();
}







