// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillWater.h"

#include "Pokemon.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

USkillWater::USkillWater()
{
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystem(TEXT("/Game/FXVarietyPack/Particles/P_ky_laser01"));

	// ��ƼŬ �ý����� �ε�Ǿ����� Ȯ�� �� ����
	if (ParticleSystem.Succeeded())
	{
		SkillParticle = ParticleSystem.Object;
	}
}

void USkillWater::SpawnParticle(APokemon* target)
{
	// Enemy�� Location�� ������ �� ��ġ�� ��ƼŬ ����
	ParticleComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SkillParticle, target->GetActorLocation());

	// 5�� �Ŀ� ��ƼŬ�� ���쵵�� ����
	GetOwner()->GetWorldTimerManager().SetTimer(SkillTimer, this, &USkillWater::DestroyParticle, TimeToDestroy, false);
}

void USkillWater::DestroyParticle()
{
	if (ParticleComp != nullptr)
	{
		ParticleComp->DestroyComponent();
	}
}

void USkillWater::WaterAttack(APokemon* target)
{
	SpawnParticle(target);
	DestroyParticle();
}
