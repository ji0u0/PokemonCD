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
	// ��� Ʈ���̳ʰ� ������ �ִ� ���ϸ��� Ÿ������ ��´�

	/*// ���� �� ��ġ�Ǿ��ִ� ���͵��� ��Ƴ��� �迭 ����
	TArray<AActor*> ActorsToFind;
	if (GetWorld())
	{
		// ���� �� �����ϴ� ���� �� AEnemy Ŭ������ ���͸� �迭�� ����
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APokemon::StaticClass(), ActorsToFind);
	}

	// ���� Ŭ���� Ÿ�� ����, �迭 ��ü Ž��
	for (AActor* target : ActorsToFind)
	{
		//Ÿ���� Null�� �ƴϸ� Enemy ĳ����
		if (target != nullptr && target != this)
		{
			Target = Cast<APokemon>(target);
		}
	}*/
}
