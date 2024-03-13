// Fill out your copyright notice in the Description page of Project Settings.


#include "PokemonWater.h"

#include "SkillWater.h"
#include "Components/BoxComponent.h"

APokemonWater::APokemonWater()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	// Box Collision
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	SetRootComponent(BoxComponent);

	// Static Mesh
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);

	SkelMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComp"));
	SkelMeshComp->SetupAttachment(RootComponent);
	/*SkelMeshComp->SetRelativeLocationAndRotation
	(
		FVector(0, 0, 25),
		FRotator(0, -90, 0)
	);
	SkelMeshComp->SetRelativeScale3D(FVector(0.1f));*/

	// Skill Components
	waterSkill = CreateDefaultSubobject<USkillWater>(TEXT("WaterSkill"));
	firstSkill = waterSkill;

	// Set info
	pokemonName = "Sobble";
	pokemonType = Type::Water;
	pokemonMaxHealth = 150;
	pokemonCurHealth = pokemonMaxHealth;
}
