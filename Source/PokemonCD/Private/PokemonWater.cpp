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
	//��ӱ� �ִϸ��̼�
	auto anim = Cast<USobbleAnimInstance>(SkelMeshComp->GetAnimInstance());
	anim->PlaySobbleNomalAttackMontage(index);
}

void APokemonWater::PlayFirstSkillAnim()
{
	Super::PlayFirstSkillAnim();
	//Ÿ�Խ�ų
	AttackingAnim(2.33f);
}

void APokemonWater::PlaySecondSkillAnim()
{
	Super::PlaySecondSkillAnim();
	//�븻������ų
	AttackingAnim(0.f);
}


void APokemonWater::PlayThirdSkillAnim()
{
	Super::PlayThirdSkillAnim();
	//�븻���º�ȯ��ų1
	AttackingAnim(3.3f);
}

void APokemonWater::PlayFourthSkillAnim()
{
	Super::PlayFourthSkillAnim();
	//�븻���º�ȯ��ų2
	AttackingAnim(3.3f);
}

/*void APokemonWater::OnMyAttack(APokemon* otherpokemon)
{
	//����, ������ϸ�, �ڼӺ���, Ÿ�Ի�1, Ÿ�Ի�2 ����
	auto attackDamage = AttackDamage(40, this); //����, ��ų�� ���� �ڼӺ���, Ÿ�Ի� ���� �� �ٽ� �ۼ�
	//������ϸ� ���� ü�¿��� attackDamage�� �A ���� ü���� �ٽ� ������ϸ� ü�¿� �ִ´�
	otherpokemon->pokemonCurHealth = otherpokemon->pokemonCurHealth - attackDamage;
}*/

