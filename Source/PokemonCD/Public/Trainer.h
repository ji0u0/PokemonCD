// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PokemonGameMode.h"
#include "WidgetChoosePokemon.h"
#include "GameFramework/Pawn.h"
#include "AutonomousPlayerController.h"
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

	UPROPERTY()
	class APokemonGameMode* GameMode;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UWidgetChoosePokemon> PokemonTemplate;

	UPROPERTY()
	class UWidgetChoosePokemon* PokemonChoose;

	UFUNCTION()
	void ChoosePokemonWidgetCreate();

	UFUNCTION()
	void CompleteChoose();

	void PossesController();

	UFUNCTION(Server,Reliable)
	void ClientPossess();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class AAutonomousPlayerController> ControllerTemplate;

	int32 PlayerIndex;

	// Components
	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere)
	class UArrowComponent* ThrowingPosition;


	/// <summary>
	/// ����ä
	/// Ʈ���̳� �޽� �߰�
	/// </summary>
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class USkeletalMeshComponent* TrainerSkelMeshComp;

	/// <summary>
	/// ����ä
	/// Ʈ���̳� �ڵ� ���� �߰� �� ball �߰�
	/// </summary>
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USceneComponent* handComp;

	void AttachBall();
	void DetachBall();

	/// <summary>
	/// ����ä
	/// �ִϸ��̼� ����
	/// </summary>
	UPROPERTY(EditDefaultsOnly)
	bool isAttachBall;

	// ����
	UPROPERTY(EditDefaultsOnly)
	class ATrainer* oppoTrainer;

	void FindOpponentTrainer();

	// ���� ���ϸ�
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

	//FVector pokemonLoc = FVector(-40.f, 830.f, 150.f);


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetMain* mainWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetSkill* skillWidget;
//<<<<<<< HEAD
//=======

//>>>>>>> fa035a90e707ee172ff735b93fe320fab9d14587
};
