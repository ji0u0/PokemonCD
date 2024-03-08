// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill.h"
#include "SkillWater.generated.h"


UCLASS()
class POKEMONCD_API USkillWater : public USkill
{
	GENERATED_BODY()

public:
	USkillWater();

	

	UFUNCTION()
	virtual void Attack(ATrainer* trainer) override;

	void SpawnParticle(AActor* target);
	void DestroyParticle();
	void CameraShake();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float TimeToDestroy = 1.5;

	// Particle
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UParticleSystem* SkillParticle;

	UPROPERTY(EditDefaultsOnly)
	class UParticleSystemComponent* ParticleComp;

	FTimerHandle SkillTimer;

	FVector myLoc;
	FVector oppoLoc;
	float alpha;
};
