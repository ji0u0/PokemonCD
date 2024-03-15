// Fill out your copyright notice in the Description page of Project Settings.


#include "PokemonWater.h"

#include "ScorBunnyAnimInstance.h"
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

	// Skill
	firstSkill = ESkill::WaterAttack;
	secondSkill = ESkill::FireAttack;
	secondSkill = ESkill::GrassAttack;

	// Set info
	pokemonName = "Sobble";
	pokemonType = EType::Water;
	pokemonMaxHealth = 150;
	pokemonCurHealth = pokemonMaxHealth;
}

void APokemonWater::BeginPlay()
{
	Super::BeginPlay();

}

void APokemonWater::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
}

void APokemonWater::AttackingNormalAnim()
{
	auto anim = Cast<UScorBunnyAnimInstance>(SkelMeshComp->GetAnimInstance());
	anim->PlayScorbunnyNomalAttackMontage();
}

void APokemonWater::AttackingTypeAnim()
{
	auto anim = Cast<UScorBunnyAnimInstance>(SkelMeshComp->GetAnimInstance());
	anim->PlayScorbunnyTypeAttackMontage();
}

void APokemonWater::AttackingAnim()
{
	auto anim = Cast<UScorBunnyAnimInstance>(SkelMeshComp->GetAnimInstance());
	// anim->PlayScorbunnyTypeAttackMontage();
}

void APokemonWater::PlayFirstSkillAnim()
{
	Super::PlayFirstSkillAnim();
	AttackingNormalAnim();
}

void APokemonWater::PlaySecondSkillAnim()
{
	Super::PlaySecondSkillAnim();
	AttackingTypeAnim();
}

