// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillWater.h"

#include "Pokemon.h"
#include "Trainer.h"
#include "WidgetSkill.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

#include "GameFramework/PlayerController.h"

USkillWater::USkillWater()
{
	skillName = "Water Skill";
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystem(TEXT("/Game/FXVarietyPack/Particles/P_ky_laser01"));

	// 파티클 시스템이 로드되었는지 확인 후 설정
	if (ParticleSystem.Succeeded())
	{
		SkillParticle = ParticleSystem.Object;
	}
}

void USkillWater::SpawnParticle(AActor* target)
{
	if(SkillParticle == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No particle"));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, "No particle");

		return;
	}

	// Enemy의 Location을 가져와 그 위치에 파티클 스폰
	ParticleComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SkillParticle, target->GetActorLocation());
	
	// 5초 후에 파티클을 지우도록 설정
	GetOwner()->GetWorldTimerManager().SetTimer(SkillTimer, this, &USkillWater::DestroyParticle, TimeToDestroy, false);
}

void USkillWater::DestroyParticle()
{
	//my trainer local인지 확인
	// if (MyTrainer->skillWidget && MyTrainer->GetController()->IsLocalController())
	APokemon* pokemon = Cast<APokemon>(GetOwner());

	if(pokemon)
	{
		pokemon->OwnedTrainer->skillWidget->SetVisibility(ESlateVisibility::Visible);
	}
	/*if (MyTrainer->skillWidget && MyTrainer->GetController()->IsLocalController())
	{
		MyTrainer->skillWidget->SetVisibility(ESlateVisibility::Visible);
	}*/
}

void USkillWater::CameraShake()
{
	// 안됨...
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if(PlayerController)
	{
		APlayerCameraManager* CameraManager = PlayerController->PlayerCameraManager;
		if (CameraManager)
		{
			// 카메라를 흔들기 위해 특정 벡터를 더합니다. 예를 들어, X축으로 10만큼 흔들어 보겠습니다.
			FVector ShakeOffset = FVector(10.f, 0.f, 0.f);

			// 카메라의 위치를 변경하여 흔들림을 시뮬레이션합니다.
			/*CameraManager->PlayWorldCameraShake(GetWorld(), UCameraShakeBase::StaticClass(), GetOwner()->GetActorLocation(),
			0.f, 1000.f, false);*/
		}
	}
}

void USkillWater::Attack(ATrainer* trainer)
{
	APokemon* target = trainer->currentPokemon;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, "Attack");
	if(trainer != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan,trainer->GetActorLabel(true));
		SpawnParticle(trainer);
	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, "oppo trainer == null");
}
