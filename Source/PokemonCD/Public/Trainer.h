// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PokemonGameMode.h"
#include "WidgetChoosePokemon.h"
#include "GameFramework/Pawn.h"
#include "Trainer.generated.h"

UENUM()
enum class EPokemonList : uint8
{
	RABIFOOT,
	SOBBLE,
	GROOKEY
};

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
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	///// 게임 모드 & 게임 스테이트 /////
	UPROPERTY()
	class APokemonGameMode* GameMode;

	UPROPERTY()
	class APokemonGameState* GameState;


	///// 컨트롤러 /////
	UPROPERTY(EditDefaultsOnly)
	class ATrainerPlayerController* PossessedController;

	void SetSpawnTag();


	///// Components /////
	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere)
	class UArrowComponent* ThrowingPosition;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class USkeletalMeshComponent* TrainerSkelMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USceneComponent* handComp;


	///// 위젯 /////
	
	// Choose Widget
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UWidgetChoosePokemon> PokemonTemplate;

	UPROPERTY()
	class UWidgetChoosePokemon* PokemonChoose;

	UFUNCTION()
	void ChoosePokemonWidgetCreate();

	UFUNCTION(Server,Reliable)
	void CompleteChoose();

	// Main (status) Widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetMain* mainWidget;

	UFUNCTION()
	void MainWidgetCreate();

	// Skill Widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetSkill* skillWidget;

	UFUNCTION()
	void SkillWidgetCreate();



	// 상대방
	UPROPERTY(EditDefaultsOnly)
	class ATrainer* oppoTrainer;

	void FindOpponentTrainer();

	///// 포켓몬 /////
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class APokemonWater> FirstPokemon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class APokemonWater> SecondPokemon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class APokemonWater> ThirdPokemon;

	UPROPERTY()
	class APokemonWater* CurrentPokemon;
	
	UPROPERTY(EditDefaultsOnly)
	EPokemonList Pokemon;

	void SetPokemon(EPokemonList Selected);

	UPROPERTY(EditDefaultsOnly)
	class APokemonWater* SelectedPokemon;

	void SpawnFirstPokemon(FTransform SpawnTransform);
	void SpawnSecondPokemon(FTransform SpawnTransform);
	void SpawnThirdPokemon(FTransform SpawnTransform);

	FActorSpawnParameters SpawnParams;
	//int32 tmp;

	// spawn pokemon
	UFUNCTION(Server, Reliable)
	void ServerSpawnPokemon();

	UFUNCTION(NetMulticast, Reliable)
	void MultiSpawnPokemon();

	///// 몬스터볼 /////
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AMonsterBall> MonsterBallFactory;

	UPROPERTY()
	class AMonsterBall* MonsterBall;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* SpawnParticle;

	void AttachBall();
	void DetachBall();

	UPROPERTY()
	bool isAttachBall;
};
