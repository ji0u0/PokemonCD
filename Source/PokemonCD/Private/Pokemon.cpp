// Fill out your copyright notice in the Description page of Project Settings.


#include "Pokemon.h"


// Sets default values
APokemon::APokemon()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APokemon::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APokemon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APokemon::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APokemon::FindTarget()
{
	// 상대 트레이너가 데리고 있는 포켓몬을 타겟으로 삼는다

	/*// 월드 상에 배치되어있는 액터들을 담아놓을 배열 선언
	TArray<AActor*> ActorsToFind;
	if (GetWorld())
	{
		// 월드 상에 존재하는 액터 중 AEnemy 클래스인 액터를 배열에 저장
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APokemon::StaticClass(), ActorsToFind);
	}

	// 액터 클래스 타겟 선언, 배열 전체 탐색
	for (AActor* target : ActorsToFind)
	{
		//타겟이 Null이 아니면 Enemy 캐스팅
		if (target != nullptr && target != this)
		{
			Target = Cast<APokemon>(target);
		}
	}*/
}
