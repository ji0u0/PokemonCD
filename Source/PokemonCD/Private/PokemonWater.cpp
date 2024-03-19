// Fill out your copyright notice in the Description page of Project Settings.


#include "PokemonWater.h"

#include "SkillWater.h"
#include "SobbleAnimInstance.h"
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

	// Skill Components
	firstSkill = ESkill::SkillWater;
	secondSkill = ESkill::SkillFire;
	thirdSkill = ESkill::SkillGrass;

	// Set info
	pokemonName = "Sobble";
	pokemonType = Type::Water;
	pokemonMaxHealth = 70;
	pokemonCurHealth = pokemonMaxHealth;
	pokemonAttack = 85.f;
	pokemonDefense = 65.f;
	pokemonSpeed = 120.f;
}

void APokemonWater::BeginPlay()
{
	Super::BeginPlay();

}

void APokemonWater::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void APokemonWater::AttackingAnim(int32 index)
{
	//울머기 애니메이션
	auto anim = Cast<USobbleAnimInstance>(SkelMeshComp->GetAnimInstance());
	anim->PlaySobbleNomalAttackMontage(index);
}

void APokemonWater::PlayFirstSkillAnim()
{
	Super::PlayFirstSkillAnim();
	//타입스킬
	AttackingAnim(0);
}

void APokemonWater::PlaySecondSkillAnim()
{
	Super::PlaySecondSkillAnim();
	//노말물리스킬
	AttackingAnim(1);
}


void APokemonWater::PlayThirdSkillAnim()
{
	Super::PlayThirdSkillAnim();
	//노말상태변환스킬1
	AttackingAnim(2);
}

void APokemonWater::PlayFourthSkillAnim()
{
	Super::PlayFourthSkillAnim();
	//노말상태변환스킬2
	AttackingAnim(3);
}

void APokemonWater::OnMyAttack()
{
	//공격하기
	//AttackDamage();
}
