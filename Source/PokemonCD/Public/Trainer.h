// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	// Components
	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere)
	class UArrowComponent* ThrowingPosition;

	// 상대방
	UPROPERTY(EditDefaultsOnly)
	class ATrainer* oppoTrainer;

	void FindOpponentTrainer();

	// 소유 포켓몬
	UPROPERTY(EditDefaultsOnly)
	class APokemon* firstPokemon = nullptr;

	UPROPERTY(EditDefaultsOnly)
	class APokemon* secondPokemon = nullptr;

	UPROPERTY(EditDefaultsOnly)
	class APokemon* thirdPokemon = nullptr;

	UPROPERTY(EditDefaultsOnly)
	class APokemon* currentPokemon = nullptr;

	// Monster Ball
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AMonsterBall> MonsterBallFactory;

	UPROPERTY()
	class AMonsterBall* MonsterBall;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* SpawnParticle;

	// spawn pokemon
	void SpawnPokemon(APokemon* pokemon);

	FVector pokemonLoc = FVector(-40.f, 830.f, 150.f);

	///// Widget /////
	UFUNCTION()
	void CreateWidget();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UMainWidget> mainWidgetFactory;

	UPROPERTY(BlueprintReadWrite)
	class UMainWidget* mainWidget;

	UPROPERTY(BlueprintReadWrite)
	class UWidgetSkill* skillWidget;

};
