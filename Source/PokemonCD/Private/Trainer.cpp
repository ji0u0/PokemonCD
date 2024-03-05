// Fill out your copyright notice in the Description page of Project Settings.


#include "Trainer.h"

#include "MonsterBall.h"
#include "Pokemon.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ATrainer::ATrainer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Box Collision
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	SetRootComponent(BoxComponent);

	// Mesh Component
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetRelativeLocation(FVector(0, 0, 70));
	MeshComponent->SetRelativeScale3D(FVector(0.5, 0.5, 2.0));

	// Arrow Component - Throwing Position
	ThrowingPosition = CreateDefaultSubobject<UArrowComponent>(TEXT("ThrowingPosition"));
	ThrowingPosition->SetupAttachment(RootComponent);
	ThrowingPosition->SetRelativeLocation(FVector(50, 0, 130));
}

// Called when the game starts or when spawned
/**
 * 
 */
void ATrainer::BeginPlay()
{
	Super::BeginPlay();
	// 1초 후 포켓몬 소환
	FTimerHandle timerHandle;
	GetWorldTimerManager().SetTimer(timerHandle, [this]() {
			SpawnPokemon(firstPokemon);
		}, 1.f, false);
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

void ATrainer::SpawnPokemon(APokemon* pokemon)
{
	FTransform ThrowingTransfrom = ThrowingPosition->GetComponentTransform();

	// 몬스터볼 생성
	MonsterBall = GetWorld()->SpawnActor<AMonsterBall>(MonsterBallFactory, ThrowingTransfrom);
	if (MonsterBall == nullptr || pokemon == nullptr) return;

	// n초 후 포켓몬 소환
	FTimerHandle timerHandle;
	GetWorldTimerManager().SetTimer(timerHandle, [this, pokemon]() {
		FTransform MonsterBallTransform = MonsterBall->GetActorTransform();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SpawnParticle, MonsterBallTransform.GetLocation());
		pokemon->SetActorLocation(MonsterBallTransform.GetLocation());
		MonsterBall->Destroy();
		}, 1.0f, false);
}

void ATrainer::CreateWidget()
{
	// Main Widget 생성 및 표시
	/*mainWidget = CreateWidget<UMainWidget>(GetWorld(), mainWidgetFactory);

	if (mainWidget != nullptr)
	{
		mainWidget->AddToViewport();
	}*/
}

/*
void ATrainer::ThrowingMonsterBall()
{
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Walking"));
	FTransform ThrowingTransfrom = ThrowingPosition->GetComponentTransform();
	
	MonsterBall = GetWorld()->SpawnActor<AMonsterBall>(MonsterBallFactory, ThrowingTransfrom);

	GetWorldTimerManager().SetTimer(MonsterBallTimer, this, &ATrainer::SpawnPokemon, SpawnDelayTime, false);
}
*/

/*void ATrainer::SpawnPokemon()
{
	// UE_LOG(LogTemp, Log, TEXT("bye"));
	GetWorldTimerManager().ClearTimer(MonsterBallTimer);

	FTransform MonsterBallTransform = MonsterBall->GetActorTransform();
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SpawnParticle, MonsterBallTransform.GetLocation());
	FirePokemon = GetWorld()->SpawnActor<AFirePokemon>(FirePokemonFactory, MonsterBallTransform);
	FirePokemon->BoxComponent->SetSimulatePhysics(true);
	MonsterBall->Destroy();
}*/

