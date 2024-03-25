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
	//Ÿ�Խ�ų
	AttackingAnim(0.f);
}

void APokemonGrass::PlaySecondSkillAnim()
{
	Super::PlaySecondSkillAnim();
	//�븻������ų
	AttackingAnim(0.f);
}

void APokemonGrass::PlayThirdSkillAnim()
{
	Super::PlayThirdSkillAnim();
	//�븻���º�ȯ��ų1
	AttackingAnim(3.1f);
}

void APokemonGrass::PlayFourthSkillAnim()
{
	Super::PlayFourthSkillAnim();
	//�븻���º�ȯ��ų2
	AttackingAnim(3.1f);
}

/*void APokemonGrass::OnMyAttack(APokemon* otherpokemon)
{
	//��ų����, ������ϸ�, �ڼӺ���, Ÿ�Ի�1, Ÿ�Ի�2 ����
	auto attackDamage = AttackDamage(40, this); //����, ��ų�� ���� �ڼӺ���, Ÿ�Ի� ���� �� �ٽ� �ۼ�
	//������ϸ� ���� ü�¿��� attackDamage�� �A ���� ü���� �ٽ� ������ϸ� ü�¿� �ִ´�
	otherpokemon->pokemonCurHealth = otherpokemon->pokemonCurHealth - attackDamage;
}*/
