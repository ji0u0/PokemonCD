// Fill out your copyright notice in the Description page of Project Settings.


#include "PokemonGrass.h"

#include "GrookeyAnimInstance.h"
#include "ScorBunnyAnimInstance.h"
#include "Components/BoxComponent.h"

APokemonGrass::APokemonGrass()
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
	pokemonName = "Grookey";
	pokemonType = Type::Grass;
	pokemonMaxHealth = 100;
	pokemonAttack = 125.f;
	pokemonDefense = 90.f;
	pokemonSpeed = 85.f;
}

void APokemonGrass::BeginPlay()
{
	Super::BeginPlay();

}

void APokemonGrass::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

void APokemonGrass::AttackingAnim(float index)
{
	auto anim = Cast<UGrookeyAnimInstance>(SkelMeshComp->GetAnimInstance());
	anim->PlayScorbunnyAttackMontage(index);
}

void APokemonGrass::PlayFirstSkillAnim()
{
	Super::PlayFirstSkillAnim();
	//타입스킬
	AttackingAnim(0.f);
}

void APokemonGrass::PlaySecondSkillAnim()
{
	Super::PlaySecondSkillAnim();
	//노말물리스킬
	AttackingAnim(0.f);
}

void APokemonGrass::PlayThirdSkillAnim()
{
	Super::PlayThirdSkillAnim();
	//노말상태변환스킬1
	AttackingAnim(3.1f);
}

void APokemonGrass::PlayFourthSkillAnim()
{
	Super::PlayFourthSkillAnim();
	//노말상태변환스킬2
	AttackingAnim(3.1f);
}

/*void APokemonGrass::OnMyAttack(APokemon* otherpokemon)
{
	//스킬위력, 상대포켓몬, 자속보정, 타입상성1, 타입상성2 설정
	auto attackDamage = AttackDamage(40, this); //더미, 스킬에 따른 자속보정, 타입상성 설정 후 다시 작성
	//상대포켓몬 현재 체력에서 attackDamage를 뺸 후의 체력을 다시 상대포켓몬 체력에 넣는다
	otherpokemon->pokemonCurHealth = otherpokemon->pokemonCurHealth - attackDamage;
}*/
