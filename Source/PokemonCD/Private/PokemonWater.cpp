// Fill out your copyright notice in the Description page of Project Settings.


#include "PokemonWater.h"

#include "SkillWater.h"
#include "Components/BoxComponent.h"

APokemonWater::APokemonWater()
{
	PrimaryActorTick.bCanEverTick = true;

	// Box Collision
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	SetRootComponent(BoxComponent);

	// Static Mesh
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);

	// Skill Components
	waterSkill = CreateDefaultSubobject<USkillWater>(TEXT("WaterSkill"));
	firstSkill = waterSkill;

	pokemonName = "Sobble";
}
