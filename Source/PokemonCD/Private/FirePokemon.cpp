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

// ���� �� ��ġ�Ǿ��ִ� ���͸� ��Ÿ�� �߿� ã��
void AFirePokemon::FindActor()
{
	// ���� �� ��ġ�Ǿ��ִ� ���͵��� ��Ƴ��� �迭 ����
	TArray<AActor*> ActorsToFind;
	if(GetWorld())
	{
		// ���� �� �����ϴ� ���� �� AEnemy Ŭ������ ���͸� �迭�� ����
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), ActorsToFind);
	}

	// ���� Ŭ���� Ÿ�� ����, �迭 ��ü Ž��
	for(AActor* target : ActorsToFind)
	{
		//Ÿ���� Null�� �ƴϸ� Enemy ĳ����
		if(target)
		{
			Enemy = Cast<AEnemy>(target);
		}
	}
}

void AFirePokemon::SpawnParticle()
{
	// Enemy�� Location�� ������ �� ��ġ�� ��ƼŬ ����
	FireParticleComponent = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SkillParticle, Enemy->GetActorLocation());

	// 5�� �Ŀ� ��ƼŬ�� ���쵵�� ����
	GetWorldTimerManager().SetTimer(SkillTimer, this, &AFirePokemon::DestroyParticle, TimeToDestroy, false);
}

void AFirePokemon::DestroyParticle()
{
	if(FireParticleComponent != nullptr)
	{
		FireParticleComponent->DestroyComponent();
	}
}




