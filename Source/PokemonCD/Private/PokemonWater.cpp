// Fill out your copyright notice in the Description page of Project Settings.


#include "PokemonWater.h"

#include "SkillWater.h"

APokemonWater::APokemonWater():APokemon()
{
	// Static Mesh
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);

	// Skill Components
	waterSkill = CreateDefaultSubobject<USkillWater>(TEXT("WaterSkill"));
	MeshComponent->SetupAttachment(RootComponent);
}
