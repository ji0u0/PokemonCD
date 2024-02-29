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

	// Static Mesh
	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* MeshComponent;

	// Skill Components
	UPROPERTY(EditDefaultsOnly)
	class USkillWater* waterSkill;
};
