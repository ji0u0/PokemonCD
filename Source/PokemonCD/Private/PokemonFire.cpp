// Fill out your copyright notice in the Description page of Project Settings.


#include "PokemonFire.h"

#include "ScorBunnyAnimInstance.h"
#include "Components/BoxComponent.h"

APokemonFire::APokemonFire()
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
	pokemonName = "Scorbunny";
	pokemonType = Type::Fire;
	pokemonMaxHealth = 80;
	pokemonAttack = 116.f;
	pokemonDefense = 75.f;
	pokemonSpeed = 119.f;
}

void APokemonFire::BeginPlay()
{
	Super::BeginPlay();

}

void APokemonFire::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void APokemonFire::AttackingAnim(int32 index)
{
	auto anim = Cast<UScorBunnyAnimInstance>(SkelMeshComp->GetAnimInstance());
	anim->PlayScorbunnyAttackMontage(index);
	
}

void APokemonFire::PlayFirstSkillAnim()
{
	Super::PlayFirstSkillAnim();
	//타입스킬
	AttackingAnim(0);
}

void APokemonFire::PlaySecondSkillAnim()
{
	Super::PlaySecondSkillAnim();
	//노말물리스킬
	AttackingAnim(1);
}

void APokemonFire::PlayThirdSkillAnim()
{
	Super::PlayThirdSkillAnim();
	//노말상태변환스킬1
	AttackingAnim(2);
}

void APokemonFire::PlayFourthSkillAnim()
{
	Super::PlayFourthSkillAnim();
	//노말상태변환스킬2
	AttackingAnim(3);
}

void APokemonFire::OnMyAttack(APokemon* otherpokemon)
{
	/*if(pokemonType == )*/


	//스킬위력, 상대포켓몬, 자속보정, 타입상성1, 타입상성2 설정
	auto attackDamage = AttackDamage(40, this); //더미, 스킬에 따른 자속보정, 타입상성 설정 후 다시 작성
	//상대포켓몬 현재 체력에서 attackDamage를 뺸 후의 체력을 다시 상대포켓몬 체력에 넣는다
	otherpokemon->pokemonCurHealth = otherpokemon->pokemonCurHealth - attackDamage;
}
