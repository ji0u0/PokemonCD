// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillWater.h"

#include "Pokemon.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

USkillWater::USkillWater()
{
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystem(TEXT("/Game/FXVarietyPack/Particles/P_ky_laser01"));

	// 파티클 시스템이 로드되었는지 확인 후 설정
	if (ParticleSystem.Succeeded())
	{
		SkillParticle = ParticleSystem.Object;
	}
}

void USkillWater::SpawnParticle(APokemon* target)
{
	// Enemy의 Location을 가져와 그 위치에 파티클 스폰
	ParticleComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SkillParticle, target->GetActorLocation());

	// 5초 후에 파티클을 지우도록 설정
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
