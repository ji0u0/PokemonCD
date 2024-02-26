// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FirePokemon.generated.h"

UCLASS()
class POKEMONCD_API AFirePokemon : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFirePokemon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* BoxComponent;

	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly)
	class UArrowComponent* SkillSpawnPos;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UParticleSystem* SkillParticle;

	UPROPERTY(EditDefaultsOnly)
	class UParticleSystemComponent* FireParticleComponent;

	UPROPERTY(EditDefaultsOnly)
	class AEnemy* Enemy;

	FTimerHandle SkillTimer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float TimeToDestroy = 1.5;

	void FindActor();
	void SpawnParticle();
	void DestroyParticle();
};
