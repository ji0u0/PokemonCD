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

	// ��ƼŬ �ý����� �ε�Ǿ����� Ȯ�� �� ����
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

	// Enemy�� Location�� ������ �� ��ġ�� ��ƼŬ ����
	ParticleComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SkillParticle, target->GetActorLocation());
	
	// 5�� �Ŀ� ��ƼŬ�� ���쵵�� ����
	GetOwner()->GetWorldTimerManager().SetTimer(SkillTimer, this, &USkillWater::DestroyParticle, TimeToDestroy, false);
}

void USkillWater::DestroyParticle()
{
	//my trainer local���� Ȯ��
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
	// �ȵ�...
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if(PlayerController)
	{
		APlayerCameraManager* CameraManager = PlayerController->PlayerCameraManager;
		if (CameraManager)
		{
			// ī�޶� ���� ���� Ư�� ���͸� ���մϴ�. ���� ���, X������ 10��ŭ ���� ���ڽ��ϴ�.
			FVector ShakeOffset = FVector(10.f, 0.f, 0.f);

			// ī�޶��� ��ġ�� �����Ͽ� ��鸲�� �ùķ��̼��մϴ�.
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
