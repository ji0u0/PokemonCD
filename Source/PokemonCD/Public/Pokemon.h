// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Pokemon.generated.h"

UENUM(BlueprintType)
enum class Type : uint8
{
	Normal UMETA(DisplayName = "Nrass"),
	Water UMETA(DisplayName = "Water"),
	Fire UMETA(DisplayName = "Fire"),
	Grass UMETA(DisplayName = "Grass")
};

UENUM(BlueprintType)
enum class ESkill : uint8
{
	SkillWater UMETA(DisplayName = "WaterGun"),
	SkillFire UMETA(DisplayName = "Ember"),
	SkillGrass UMETA(DisplayName = "LeafStorm")
};

UCLASS()
class POKEMONCD_API APokemon : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APokemon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float timeDeltaTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class ATrainer* OwnedTrainer;

	///// status /////
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FString pokemonName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	Type pokemonType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int pokemonMaxHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int pokemonCurHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float pokemonAttack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float pokemonDefense;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float pokemonSpeed;

	///// Skill /////
	ESkill firstSkill = ESkill::SkillWater;	//타입스킬
	ESkill secondSkill = ESkill::SkillFire;	//노말물리스킬
	ESkill thirdSkill = ESkill::SkillGrass;	//노말상태변환스킬1
	ESkill fourthSkill = ESkill::SkillGrass;	//노말상태변환스킬2

	UFUNCTION()
	void Skill(ESkill Skill);

	virtual void PlayFirstSkillAnim() {};
	virtual void PlaySecondSkillAnim() {};
	virtual void PlayThirdSkillAnim() {};
	virtual void PlayFourthSkillAnim() {};

	// Particle
	UParticleSystem* ThrowParticle;

	UParticleSystem* HitParticle;

	FVector myLoc;

	FVector oppoLoc;

	FTimerHandle handle;

	float alpha = 0.f;

	// Camera Shake -> 포켓몬을 만들면 꼭 Factory를 채울 것
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCameraShakeBase> WaterCameraShakeFactory;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCameraShakeBase> GrassCameraShakeFactory;


	//--------------------------------포켓몬 공격력------------------------------
	int32 AttackDamage(float power, APokemon* otherPokemon , int32 sameType, int32 typecompat1, int32 typecompat2);
};
