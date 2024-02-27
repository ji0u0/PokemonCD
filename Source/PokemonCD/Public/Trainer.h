// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FirePokemon.h"
#include "MonsterBall.h"
#include "GameFramework/Pawn.h"
#include "Trainer.generated.h"

UCLASS()
class POKEMONCD_API ATrainer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATrainer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AFirePokemon> FirePokemon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AMonsterBall> MonsterBallFactory;
	AMonsterBall* MonsterBall;

	UPROPERTY(EditAnywhere)
	class UArrowComponent* ThrowingPosition;

	FTimerHandle MonsterBallTimer;

	void ThrowingMonsterBall();
	void SpawnPokemon();
};
