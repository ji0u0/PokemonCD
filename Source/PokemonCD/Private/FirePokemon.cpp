// Fill out your copyright notice in the Description page of Project Settings.


#include "FirePokemon.h"

#include "Enemy.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

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
	SetActorRelativeRotation(FRotator());
	/*FindActor();
	SpawnParticle();*/

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

// 월드 상에 배치되어있는 액터를 런타임 중에 찾음
void AFirePokemon::FindActor()
{
	// 월드 상에 배치되어있는 액터들을 담아놓을 배열 선언
	TArray<AActor*> ActorsToFind;
	if(GetWorld())
	{
		// 월드 상에 존재하는 액터 중 AEnemy 클래스인 액터를 배열에 저장
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), ActorsToFind);
	}

	// 액터 클래스 타겟 선언, 배열 전체 탐색
	for(AActor* target : ActorsToFind)
	{
		//타겟이 Null이 아니면 Enemy 캐스팅
		if(target)
		{
			Enemy = Cast<AEnemy>(target);
		}
	}
}

void AFirePokemon::SpawnParticle()
{
	// Enemy의 Location을 가져와 그 위치에 파티클 스폰
	FireParticleComponent = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SkillParticle, Enemy->GetActorLocation());

	// 5초 후에 파티클을 지우도록 설정
	GetWorldTimerManager().SetTimer(SkillTimer, this, &AFirePokemon::DestroyParticle, TimeToDestroy, false);
}

void AFirePokemon::DestroyParticle()
{
	if(FireParticleComponent != nullptr)
	{
		FireParticleComponent->DestroyComponent();
	}
}




