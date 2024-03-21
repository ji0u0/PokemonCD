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
	//Ÿ�Խ�ų
	AttackingAnim(0);
}

void APokemonFire::PlaySecondSkillAnim()
{
	Super::PlaySecondSkillAnim();
	//�븻������ų
	AttackingAnim(1);
}

void APokemonFire::PlayThirdSkillAnim()
{
	Super::PlayThirdSkillAnim();
	//�븻���º�ȯ��ų1
	AttackingAnim(2);
}

void APokemonFire::PlayFourthSkillAnim()
{
	Super::PlayFourthSkillAnim();
	//�븻���º�ȯ��ų2
	AttackingAnim(3);
}

void APokemonFire::OnMyAttack(APokemon* otherpokemon)
{
	/*if(pokemonType == )*/


	//��ų����, ������ϸ�, �ڼӺ���, Ÿ�Ի�1, Ÿ�Ի�2 ����
	auto attackDamage = AttackDamage(40, this); //����, ��ų�� ���� �ڼӺ���, Ÿ�Ի� ���� �� �ٽ� �ۼ�
	//������ϸ� ���� ü�¿��� attackDamage�� �A ���� ü���� �ٽ� ������ϸ� ü�¿� �ִ´�
	otherpokemon->pokemonCurHealth = otherpokemon->pokemonCurHealth - attackDamage;
}
