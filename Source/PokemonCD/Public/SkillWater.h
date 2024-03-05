// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill.h"
#include "SkillWater.generated.h"

/**
 * 
 */
UCLASS()
class POKEMONCD_API USkillWater : public USkill
{
	GENERATED_BODY()

public:
	USkillWater();

	void SpawnParticle(class APokemon* target);
	void DestroyParticle();

	void WaterAttack(class APokemon* target);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float TimeToDestroy = 1.5;

	// Particle
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UParticleSystem* SkillParticle;

	UPROPERTY(EditDefaultsOnly)
	class UParticleSystemComponent* ParticleComp;

	FTimerHandle SkillTimer;
};
