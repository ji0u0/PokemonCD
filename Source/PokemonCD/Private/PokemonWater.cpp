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

void APokemonWater::AttackingAnim(float index)
{
	//울머기 애니메이션
	auto anim = Cast<USobbleAnimInstance>(SkelMeshComp->GetAnimInstance());
	anim->PlaySobbleNomalAttackMontage(index);
}

void APokemonWater::PlayFirstSkillAnim()
{
	Super::PlayFirstSkillAnim();
	//타입스킬
	AttackingAnim(2.33f);
}

void APokemonWater::PlaySecondSkillAnim()
{
	Super::PlaySecondSkillAnim();
	//노말물리스킬
	AttackingAnim(0.f);
}


void APokemonWater::PlayThirdSkillAnim()
{
	Super::PlayThirdSkillAnim();
	//노말상태변환스킬1
	AttackingAnim(3.3f);
}

void APokemonWater::PlayFourthSkillAnim()
{
	Super::PlayFourthSkillAnim();
	//노말상태변환스킬2
	AttackingAnim(3.3f);
}

/*void APokemonWater::OnMyAttack(APokemon* otherpokemon)
{
	//위력, 상대포켓몬, 자속보정, 타입상성1, 타입상성2 설정
	auto attackDamage = AttackDamage(40, this); //더미, 스킬에 따른 자속보정, 타입상성 설정 후 다시 작성
	//상대포켓몬 현재 체력에서 attackDamage를 뺸 후의 체력을 다시 상대포켓몬 체력에 넣는다
	otherpokemon->pokemonCurHealth = otherpokemon->pokemonCurHealth - attackDamage;
}*/

