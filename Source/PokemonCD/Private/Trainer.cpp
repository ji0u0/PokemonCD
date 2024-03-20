// Fill out your copyright notice in the Description page of Project Settings.


#include "Trainer.h"
#include "MonsterBall.h"
#include "Pokemon.h"
#include "PokemonGameState.h"
#include "PokemonWater.h"
#include "TrainerAnimInstance.h"
#include "TrainerPlayerController.h"
#include "WidgetSkill.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "WidgetChoosePokemon.h"
#include "WidgetMain.h"
#include "WidgetSkill.h"
#include "GameFramework/PlayerState.h"


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

    // SpawnParams로 스폰 조건 설정 -> 항상 스폰되도록
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    SpawnParams.bNoFail = true;
    bReplicates = true;
}

// Called when the game starts or when spawned
/**
 *
 */
void ATrainer::BeginPlay()
{
    Super::BeginPlay();
    PossessedController = Cast<ATrainerPlayerController>(Controller);
    ChoosePokemonWidgetCreate();

}

void ATrainer::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    if (HasAuthority())
    {
        GameMode = GetWorld()->GetAuthGameMode<APokemonGameMode>();
        GameState = GameMode->GetGameState<APokemonGameState>();
    }
    PossessedController = Cast<ATrainerPlayerController>(NewController);
    //PossessedController = Cast<ATrainerPlayerController>(GetWorld()->GetFirstLocalPlayerFromController());


    //HasAuthority() ? PossesController() : ClientPossess_Implementation();APokemonWater* SpawnPokemon

    //// 1초 후 띄우고
    //FTimerHandle timerHandle;
    //GetWorldTimerManager().SetTimer(timerHandle, [this]() {
    //   // 포켓몬을 소환한다
    //   SpawnPokemon(firstPokemon);
    //   // 상대 트레이너를 찾는다
    //   FindOpponentTrainer();
    //   }, 1.f, false);


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
    if (nullptr == mesh)   return;
    mesh->SetSimulatePhysics(true);
    mesh->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
    MonsterBall->Destroy();

    FTransform ThrowingTransfrom = ThrowingPosition->GetComponentTransform();
    MonsterBall = GetWorld()->SpawnActor<AMonsterBall>(MonsterBallFactory, ThrowingTransfrom);
    MonsterBall->SetActorRelativeScale3D(FVector(0.1f));
}

void ATrainer::SetSpawnTag()
{
    if (GetLocalRole() == ROLE_Authority)
        Tags.AddUnique(TEXT("Authority"));
    else
        Tags.AddUnique(TEXT("Autonomous"));
}

// Called every frame
void ATrainer::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    /*if (GetController() == nullptr)
    {
       UE_LOG(LogTemp, Warning, TEXT("%s:controller null"), *this->GetName())
          return;
    }*/

    ////오너가 있는가?
    //FString owner = GetOwner() ? GetOwner()->GetName() : TEXT("No Owner");
    //// NetConnection이 있는가?
    //FString conn = GetNetConnection() ? TEXT("Valid") : TEXT("Invalid");
    //// LocalRole
    //FString localRole = UEnum::GetValueAsString<ENetRole>(GetLocalRole());
    //// RemoteRole
    //FString remoteRole = UEnum::GetValueAsString<ENetRole>(GetRemoteRole());

    //FString nameController = GetWorld()->GetFirstPlayerController()->GetName();

    //FString isPossessed = PossessedController ? TEXT("Possess") : TEXT("not Possess");

    //FString str = FString::Printf(TEXT("Owner : %s\nConnection : %s\nlocalRole : %s\nremoteRole : %s\nController : %s\nisPossess : %s"), *owner, *conn, *localRole, *remoteRole, *nameController, *isPossessed);

    //FVector loc = GetActorLocation() + FVector(0, 0, 50);
    //DrawDebugString(GetWorld(), loc, str, nullptr, FColor::Red, 0, false, 0.75f);
}

//// Called to bind functionality to input
//void ATrainer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//   Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//}

void ATrainer::ChoosePokemonWidgetCreate()
{
    if (nullptr == PossessedController)
    {
        UE_LOG(LogTemp, Warning, TEXT("ChoosePokemonWidgetCreate  nullptr == PossessedController "));
        return;
    }

    if (IsLocallyControlled())
    {
        if (nullptr == PossessedController->PokemonChoose)
        {
            UE_LOG(LogTemp, Warning, TEXT("ChoosePokemonWidgetCreate 생성 성공!!"));
            PossessedController->PokemonChoose = CreateWidget<UWidgetChoosePokemon>(GetWorld(), PossessedController->PokemonTemplate);
            PossessedController->PokemonChoose->AddToViewport(0);

            PossessedController->PokemonChoose->trainer = this;
            PossessedController->PokemonChoose->_PlayerController = PossessedController;
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("ChoosePokemonWidgetCreate nullptr == PossessedController->PokemonChoose"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("ChoosePokemonWidgetCreate false == IsLocallyControlled()"));
    }

    //<<<<<<< Updated upstream
    //pc->PokemonChoose->trainer = this;
    ////=======
    //if (PokemonChoose)
    //{
    //   PokemonChoose->trainer = this;
    //}
    //>>>>>>> Stashed changes
}

void ATrainer::CompleteChoose_Implementation()
{
        GameState = GetWorld()->GetAuthGameMode()->GetGameState<APokemonGameState>();
        //if(GetLocalRole() == ROLE_Authority && GetRemoteRole() == ROLE_AutonomousProxy)
        if (Controller->HasAuthority())
        {
            GameState->bAuthoritySelectPokemon = true;
        }
        //else if(GetLocalRole() == ROLE_AutonomousProxy && GetRemoteRole() == ROLE_AutonomousProxy)
        else
        {
            GameState->bAutonomousSelectPokemon = true;
        }
}

void ATrainer::MainWidgetCreate()
{
    if (PossessedController)
    {
        PossessedController->MainWidget = CreateWidget<UWidgetMain>(GetWorld(), PossessedController->MainWidgetTemplate);
        PossessedController->MainWidget->AddToViewport(0);
    }
}

void ATrainer::SkillWidgetCreate()
{
    if (PossessedController)
    {
        PossessedController->SkillWidget = CreateWidget<UWidgetSkill>(GetWorld(), PossessedController->SkillWidgetTemplate);
        if(PossessedController->SkillWidget)
        {
            PossessedController->SkillWidget->AddToViewport(0);
            //PossessedController->SkillWidget->SetSkillName(CurrentPokemon);
        }
    }
}

void ATrainer::AutonomousCompleteChoose_Implementation()
{
    auto gs = GetWorld()->GetGameState<APokemonGameState>();
    if(gs)
        gs->bAutonomousSelectPokemon = true;
}

void ATrainer::AuthorityCompleteChoose_Implementation()
{
    auto gs = GetWorld()->GetGameState<APokemonGameState>();
    if(gs)
        gs->bAuthoritySelectPokemon = true;
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

    CurrentPokemon = GetWorld()->SpawnActor<APokemonWater>(FirstPokemon, SpawnTransform, SpawnParams);
    CurrentPokemon->SetActorRelativeRotation(FRotator(this->GetActorRotation()));
    //MonsterBall->Destroy();
}

void ATrainer::SpawnSecondPokemon(FTransform SpawnTransform)
{
    CurrentPokemon = GetWorld()->SpawnActor<APokemonWater>(SecondPokemon, SpawnTransform, SpawnParams);
    CurrentPokemon->SetActorRelativeRotation(FRotator(this->GetActorRotation()));
    CurrentPokemon->SetActorRelativeScale3D(FVector(1.f));
    //MonsterBall->Destroy();
}

void ATrainer::SpawnThirdPokemon(FTransform SpawnTransform)
{
    CurrentPokemon = GetWorld()->SpawnActor<APokemonWater>(ThirdPokemon, SpawnTransform, SpawnParams);
    CurrentPokemon->SetActorRelativeRotation(FRotator(this->GetActorRotation()));
    //MonsterBall->Destroy();
}

void ATrainer::tmp()
{
    UE_LOG(LogTemp, Warning, TEXT("ServerSpawnPokemon_Implementation 1"));
    FTransform ThrowingTransfrom = ThrowingPosition->GetComponentTransform();

    // 몬스터볼 생성
    MonsterBall = GetWorld()->SpawnActor<AMonsterBall>(MonsterBallFactory, ThrowingTransfrom);
    AttachBall();
    MonsterBall->SetActorRelativeScale3D(FVector(1.f));
    if (MonsterBall == nullptr) //|| currentPokemon == nullptr) 
        return;

    // 1초 후 포켓몬 소환
    FTimerHandle timerHandle;
    GetWorldTimerManager().SetTimer(timerHandle, [&] {
        // 몬스터볼

        FTransform MonsterBallTransform = MonsterBall->GetActorTransform();
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SpawnParticle, MonsterBallTransform.GetLocation());

        
        MonsterBall->Destroy();
        // currentPokemon
        //skillWidget->SetSkillName(currentPokemon);
        }, 1.25f, false);
}

void ATrainer::MultiSpawnPokemon_Implementation(EPokemonList choosePokemon)
{
    UE_LOG(LogTemp, Warning, TEXT("ServerSpawnPokemon_Implementation 1"));
    FTransform ThrowingTransfrom = ThrowingPosition->GetComponentTransform();

    // 몬스터볼 생성
    MonsterBall = GetWorld()->SpawnActor<AMonsterBall>(MonsterBallFactory, ThrowingTransfrom);
    AttachBall();
    MonsterBall->SetActorRelativeScale3D(FVector(1.f));
    if (MonsterBall == nullptr) //|| currentPokemon == nullptr) 
        return;

    // 1초 후 포켓몬 소환
    FTimerHandle timerHandle;
    GetWorldTimerManager().SetTimer(timerHandle, [&, choosePokemon] {
        // 몬스터볼

        FTransform MonsterBallTransform = MonsterBall->GetActorTransform();
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SpawnParticle, MonsterBallTransform.GetLocation());

        // 포켓몬 소환(?)
        if (Controller == nullptr)
        {
            return;
        }
        PossessedController = Cast<ATrainerPlayerController>(Controller);

        if (PossessedController == nullptr)
        {
            return;
        }
        //FString sss = UEnum::GetValueAsString(spawnPokemonType);

        UE_LOG(LogTemp, Warning, TEXT("ServerSpawnPokemon_Implementation ChoosePokeMon ------> %d"), choosePokemon);
        switch (choosePokemon)
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
        }, 1.25f, false);

    //Original
	//ServerSpawnPokemon_Implementation(choosePokemon);
}

void ATrainer::ServerSpawnPokemon_Implementation(EPokemonList choosePokemon)
{
    //MultiSpawnPokemon(choosePokemon);

#pragma region Original
    UE_LOG(LogTemp, Warning, TEXT("ServerSpawnPokemon_Implementation 1"));
    //MultiSpawnPokemon();
    FTransform ThrowingTransfrom = ThrowingPosition->GetComponentTransform();

    // 몬스터볼 생성
    MonsterBall = GetWorld()->SpawnActor<AMonsterBall>(MonsterBallFactory, ThrowingTransfrom);
    AttachBall();
    MonsterBall->SetActorRelativeScale3D(FVector(1.f));
    if (MonsterBall == nullptr) //|| currentPokemon == nullptr) 
        return;

    // 1초 후 포켓몬 소환
    FTimerHandle timerHandle;
    GetWorldTimerManager().SetTimer(timerHandle, [&, choosePokemon] {
        // 몬스터볼

        FTransform MonsterBallTransform = MonsterBall->GetActorTransform();
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SpawnParticle, MonsterBallTransform.GetLocation());

        // 포켓몬 소환(?)
        if (Controller == nullptr)
        {
            return;
        }
        PossessedController = Cast<ATrainerPlayerController>(Controller);

        if (PossessedController == nullptr)
        {
            return;
        }
        //FString sss = UEnum::GetValueAsString(spawnPokemonType);

        UE_LOG(LogTemp, Warning, TEXT("ServerSpawnPokemon_Implementation ChoosePokeMon ------> %d"), choosePokemon);
        switch (choosePokemon)
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
#pragma endregion
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
