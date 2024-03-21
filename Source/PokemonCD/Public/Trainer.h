// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PokemonGameMode.h"
#include "WidgetChoosePokemon.h"
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

	virtual void PossessedBy(AController* NewController) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	UPROPERTY()
	class APokemonGameMode* GameMode;

	UPROPERTY()
	class APokemonGameState* GameState;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UWidgetChoosePokemon> PokemonTemplate;

	UPROPERTY()
	class UWidgetChoosePokemon* PokemonChoose;

	UFUNCTION()
	void ChoosePokemonWidgetCreate();

	UFUNCTION()
	void MainWidgetCreate();

	UFUNCTION()
	void SkillWidgetCreate();

	UFUNCTION(Server,Reliable)
	void CompleteChoose();

	UFUNCTION(Server,Reliable)
	void AuthorityCompleteChoose();

	UFUNCTION(Server,Reliable)
	void AutonomousCompleteChoose();
	
	UPROPERTY(EditDefaultsOnly)
	class ATrainerPlayerController* PossessedController;

	int32 PlayerIndex;

	// Components
	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere)
	class UArrowComponent* ThrowingPosition;


	/// <summary>
	/// 노은채
	/// 트레이너 메시 추가
	/// </summary>
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class USkeletalMeshComponent* TrainerSkelMeshComp;

	/// <summary>
	/// 노은채
	/// 트레이너 핸드 소켓 추가 및 ball 추가
	/// </summary>
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USceneComponent* handComp;

	void AttachBall();
	void DetachBall();

	void SetSpawnTag();

	/// <summary>
	/// 노은채
	/// 애니메이션 조건
	/// </summary>
	UPROPERTY(EditDefaultsOnly)
	bool isAttachBall;

	// 상대방
	UPROPERTY(EditDefaultsOnly)
	class ATrainer* oppoTrainer;

	void FindOpponentTrainer();

	// 소유 포켓몬
	/*UPROPERTY(EditDefaultsOnly)
	class APokemon* firstPokemon = nullptr;*/

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
	void ServerSpawnPokemon(EPokemonList choosePokemon);

	UFUNCTION(NetMulticast, Reliable)
	void MultiSpawnPokemon(EPokemonList choosePokemon);

	void tmp();
	// Monster Ball
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AMonsterBall> MonsterBallFactory;

	UPROPERTY()
	class AMonsterBall* MonsterBall;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* SpawnParticle;


	//FVector pokemonLoc = FVector(-40.f, 830.f, 150.f);


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetMain* mainWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetSkill* skillWidget;
//<<<<<<< HEAD
//=======

//>>>>>>> fa035a90e707ee172ff735b93fe320fab9d14587
};
