// Fill out your copyright notice in the Description page of Project Settings.


#include "Pokemon.h"

#include "Kismet/GameplayStatics.h"


// Sets default values
APokemon::APokemon()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APokemon::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APokemon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	timeDeltaTime += DeltaTime;
}

// Called to bind functionality to input
void APokemon::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APokemon::Skill(ESkill Skill)
{
	myLoc = GetActorLocation();
	oppoLoc = FVector(0.f); // 꼭 바꿔줘!!!!!!!!!!!!

	switch (Skill)
	{
	case ESkill::WaterGun:
		// 물대포 파티클
		ThrowParticle = LoadObject<UParticleSystem>(nullptr, TEXT("/Game/JIU/Particle/P_Waterthrower.P_Waterthrower"));
		if (ThrowParticle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ThrowParticle, myLoc, GetActorUpVector().Rotation(), FVector(0.5f, 0.5f, 1.0f));
			// 1초 뒤에 실행
			GetWorldTimerManager().SetTimer(handle, [&]()
			{
				// 스플래시 파티클
				HitParticle = LoadObject<UParticleSystem>(nullptr, TEXT("/Game/JIU/Particle/P_WaterExplosion.P_WaterExplosion"));
				if (HitParticle && WaterCameraShakeFactory)
				{
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, oppoLoc);
					// 카메라 쉐이크
					UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraShake(WaterCameraShakeFactory);
				}
			}, 1.f, false);
		}
		break;
	case ESkill::Ember:
		ThrowParticle = LoadObject<UParticleSystem>(nullptr, TEXT("/Game/JIU/Particle/P_ky_waterBallHit.P_ky_waterBallHit"));
		if (ThrowParticle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ThrowParticle, myLoc);
			UE_LOG(LogTemp, Warning, TEXT("ok"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("so sad"));
		}
		GetWorldTimerManager().SetTimer(handle, [&]()
		{
			FVector Loc = FMath::Lerp(myLoc, oppoLoc, alpha);
			// Shoot 파티클
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ThrowParticle, Loc);
			alpha += 0.1f;
			if (alpha >= 1.0f)
			{
				alpha = 0.f;
				HitParticle = LoadObject<UParticleSystem>(nullptr, TEXT("/Game/JIU/Particle/P_ky_waterBallHit.P_ky_waterBallHit"));
				// Hit 파티클
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, oppoLoc);
				// Camera Shake
				UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraShake(WaterCameraShakeFactory);
				GetWorldTimerManager().ClearTimer(handle);
			}
		}, 0.1f, true);
		break;
	case ESkill::LeafStorm:
		HitParticle = LoadObject<UParticleSystem>(nullptr, TEXT("/Game/JIU/Particle/P_ky_storm.P_ky_storm"));
		// Hit 파티클
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, oppoLoc);
		// Camera Shake
		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraShake(GrassCameraShakeFactory);
	}
}

void APokemon::PlayFirstSkillAnim()
{
}
