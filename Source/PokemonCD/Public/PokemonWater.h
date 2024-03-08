// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pokemon.h"
#include "PokemonWater.generated.h"

/**
 * 
 */
UCLASS()
class POKEMONCD_API APokemonWater : public APokemon
{
	GENERATED_BODY()
	
public:
	APokemonWater();
	virtual void Tick(float DeltaSeconds) override;

	// Components
	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* SkelMeshComp;

	// Skills
	UPROPERTY(BlueprintReadWrite)
	class USkillWater* waterSkill;

	//애니메이션
	void AttackingAnim();
};
