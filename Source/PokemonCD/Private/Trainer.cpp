// Fill out your copyright notice in the Description page of Project Settings.


#include "Trainer.h"
#include "MonsterBall.h"
#include "Pokemon.h"
#include "PokemonGameState.h"
#include "PokemonWater.h"
#include "TrainerAnimInstance.h"
#include "WidgetSkill.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "WidgetChoosePokemon.h"


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

	TrainerSkelMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComp"));
	TrainerSkelMeshComp->SetupAttachment(RootComponent);
	TrainerSkelMeshComp->SetRelativeRotation
	(
		/*FVector(0, 0, -80),*/
		FRotator(0, -90, 0)
	);
	TrainerSkelMeshComp->SetRelativeScale3D(FVector(0.3f));

	/*BallComp = CreateDefaultSubobject<USceneComponent>(TEXT("BallComp"));
	BallComp->SetupAttachment(GetMesh);
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempBallMesh(TEXT("/Script/Engine.StaticMesh'/Game/NEC/Model/PokeBall/NormalB/StaticMesh_NormalBall.StaticMesh_NormalBall'"));
	if(tempBallMesh.Succeeded())
	{
		;
	}*/

	TrainerSkelMeshComp->SetRelativeLocationAndRotation
	(
		FVector(0, 0, 25),
		FRotator(0, -90, 0)
	);
	TrainerSkelMeshComp->SetRelativeScale3D(FVector(0.1f));

	handComp = CreateDefaultSubobject<USceneComponent>(TEXT("handComp"));
	handComp->SetupAttachment(TrainerSkelMeshComp, TEXT("PokeBallPoint"));
	handComp->SetRelativeLocationAndRotation(
		FVector(-0.936682f, -80.906958f, 32.031394f),
		FRotator(180, -90., 0));
	handComp->SetRelativeScale3D(FVector(0.3f));
}

// Called when the game starts or when spawned
/**
 *
 */
void ATrainer::BeginPlay()
{
	Super::BeginPlay();
	bReplicates = true;
	GameMode = GetWorld()->GetAuthGameMode<APokemonGameMode>();





	//HasAuthority() ? PossesController() : ClientPossess_Implementation();APokemonWater* SpawnPokemon

	//// 1초 후 띄우고
	//FTimerHandle timerHandle;
	//GetWorldTimerManager().SetTimer(timerHandle, [this]() {
	//	// 포켓몬을 소환한다
	//	SpawnPokemon(firstPokemon);
	//	// 상대 트레이너를 찾는다
	//	FindOpponentTrainer();
	//	}, 1.f, false);

	ChoosePokemonWidgetCreate();
}
void ATrainer::AttachBall()
{
	auto mesh = MonsterBall->GetComponentByClass<UStaticMeshComponent>();
	mesh->SetSimulatePhysics(false);
	mesh->AttachToComponent(handComp, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("PokeBallPoint"));
	auto anim = Cast<UTrainerAnimInstance>(TrainerSkelMeshComp->GetAnimInstance());
	anim->PlayThrowMontage();
}

void ATrainer::DetachBall()
{
	auto mesh = MonsterBall->GetComponentByClass<UStaticMeshComponent>();
	if (nullptr == mesh)	return;
	mesh->SetSimulatePhysics(true);
	mesh->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	MonsterBall->Destroy();

	FTransform ThrowingTransfrom = ThrowingPosition->GetComponentTransform();
	MonsterBall = GetWorld()->SpawnActor<AMonsterBall>(MonsterBallFactory, ThrowingTransfrom);
	MonsterBall->SetActorRelativeScale3D(FVector(0.1f));
}

// Called every frame
void ATrainer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetController() == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s:controller null"), *this->GetName())
			return;
	}
}

//// Called to bind functionality to input
//void ATrainer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//}

void ATrainer::ChoosePokemonWidgetCreate()
{
	PokemonChoose = CreateWidget<UWidgetChoosePokemon>(GetWorld(), PokemonTemplate);
	PokemonChoose->AddToViewport(0);
	//<<<<<<< Updated upstream
	PokemonChoose->trainer = this;
	//=======
	if (PokemonChoose)
	{
		PokemonChoose->trainer = this;
	}
	//>>>>>>> Stashed changes
}

void ATrainer::CompleteChoose()
{
	/*GameState = GetWorld()->GetGameState<APokemonGameStateBase>();
	if (HasAuthority())
	{
		GameState->AuthoritySelectPokemon = true;
	}
	else
	{
		GameState->AutonomousSelectPokemon = true;
	}*/

	GameState = GetWorld()->GetGameState<APokemonGameState>();
	if (GameState)
	{
		if (this->HasAuthority() && this->GetController()->IsLocalPlayerController())
			GameState->AuthoritySelectPokemon = true;
		else
			GameState->AutonomousSelectPokemon = true;
	}

}

void ATrainer::FindOpponentTrainer()
{
	// 서버에서 상대 트레이너를 찾는다... 로 변경 요망

	// 월드 상에 배치되어있는 액터들을 담아놓을 배열 선언
	TArray<AActor*> ActorsToFind;
	if (GetWorld())
	{
		// 월드 상에 존재하는 액터 중 AEnemy 클래스인 액터를 배열에 저장
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATrainer::StaticClass(), ActorsToFind);
	}

	// 액터 클래스 타겟 선언, 배열 전체 탐색
	for (AActor* target : ActorsToFind)
	{
		//타겟이 Null이 아니면 Enemy 캐스팅
		if (target != nullptr && target != this)
		{
			oppoTrainer = Cast<ATrainer>(target);
		}
	}
}

void ATrainer::SetPokemon(EPokemonList Selected)
{
	Pokemon = Selected;
}

void ATrainer::SpawnFirstPokemon(FTransform SpawnTransform)
{
	CurrentPokemon = GetWorld()->SpawnActor<APokemonWater>(FirstPokemon, SpawnTransform);
}

void ATrainer::SpawnSecondPokemon(FTransform SpawnTransform)
{
	CurrentPokemon = GetWorld()->SpawnActor<APokemonWater>(SecondPokemon, SpawnTransform);
}

void ATrainer::SpawnThirdPokemon(FTransform SpawnTransform)
{
	CurrentPokemon = GetWorld()->SpawnActor<APokemonWater>(ThirdPokemon, SpawnTransform);
}


void ATrainer::SpawnPokemon()
{
	FTransform ThrowingTransfrom = ThrowingPosition->GetComponentTransform();

	// 몬스터볼 생성
	MonsterBall = GetWorld()->SpawnActor<AMonsterBall>(MonsterBallFactory, ThrowingTransfrom);
	AttachBall();
	MonsterBall->SetActorRelativeScale3D(FVector(1.f));
	if (MonsterBall == nullptr) //|| currentPokemon == nullptr) 
		return;

	// 1초 후 포켓몬 소환
	FTimerHandle timerHandle;
	GetWorldTimerManager().SetTimer(timerHandle, [this]() {
		// 몬스터볼
		FTransform MonsterBallTransform = MonsterBall->GetActorTransform();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SpawnParticle, MonsterBallTransform.GetLocation());

		// 포켓몬 소환(?)

		switch (Pokemon)
		{
		case EPokemonList::RABIFOOT:	
			SpawnFirstPokemon(MonsterBallTransform);
			break;
		case EPokemonList::SOBBLE:			
			SpawnSecondPokemon(MonsterBallTransform);
			break;
		case EPokemonList::GROOKEY:		
			SpawnThirdPokemon(MonsterBallTransform);
			break;
		}

		MonsterBall->Destroy();

		// currentPokemon
		//skillWidget->SetSkillName(currentPokemon);
		}, 2.0f, false);
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

