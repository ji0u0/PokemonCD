// Fill out your copyright notice in the Description page of Project Settings.


#include "Pokemon.h"

#include "Trainer.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "Net/UnrealNetwork.h"


// Sets default values
APokemon::APokemon()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WaterThrowParticle = LoadObject<UParticleSystem>(nullptr, TEXT("/Game/JIU/Particle/P_Waterthrower.P_Waterthrower"));
	WaterHitParticle = LoadObject<UParticleSystem>(nullptr, TEXT("/Game/JIU/Particle/P_WaterExplosion.P_WaterExplosion"));
	FireThrowParticle = LoadObject<UParticleSystem>(nullptr, TEXT("/Game/JIU/Particle/P_ky_waterBallHit.P_ky_waterBallHit"));
	FireHitParticle = LoadObject<UParticleSystem>(nullptr, TEXT("/Game/JIU/Particle/P_ky_waterBallHit.P_ky_waterBallHit"));
	GrassHitParticle = LoadObject<UParticleSystem>(nullptr, TEXT("/Game/JIU/Particle/P_ky_storm.P_ky_storm"));

}

// Called when the game starts or when spawned
void APokemon::BeginPlay()
{
	Super::BeginPlay();
	//처음 태어날때는 현재 체력 = max체력
	pokemonCurHealth = pokemonMaxHealth;
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
	oppoLoc = OwnedTrainer->oppoTrainer->GetActorLocation();

	/*switch (Skill)
	{
	case ESkill::SkillWater:
		// 물대포 파티클
		ThrowParticle = LoadObject<UParticleSystem>(nullptr, TEXT("/Game/JIU/Particle/P_Waterthrower.P_Waterthrower"));
		if (ThrowParticle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ThrowParticle, myLoc, GetActorForwardVector().Rotation()/*, FVector(0.5f, 0.5f, 1.0f)#1#);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ThrowParticle, myLoc, GetActorRightVector().Rotation()/*, FVector(0.5f, 0.5f, 1.0f)#1#);
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
		//자속보정 계산
		if (this->pokemonType == Type::Water)
		{
			sameType = 1.5f;
		}
		else
		{
			sameType = 1.f;
		}

		//스킬 위력에 따른 데미지 계산, 물대포(위력 : 50/ 명중률 : 100)
		AttackDamage(50.f, OwnedTrainer->oppoTrainer->CurrentPokemon);

		break;
	case ESkill::SkillFire:

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

		//자속보정 계산
		if (this->pokemonType == Type::Fire)
		{
			sameType = 1.5f;
		}
		else
		{
			sameType = 1.f;
		}
		//스킬 위력에 따른 데미지 계산, 불꽃세례(위력 : 50/ 명중률 : 100)
		AttackDamage(50.f, OwnedTrainer->oppoTrainer->CurrentPokemon);
		break;
	case ESkill::SkillGrass:
		HitParticle = LoadObject<UParticleSystem>(nullptr, TEXT("/Game/JIU/Particle/P_ky_storm.P_ky_storm"));
		// Hit 파티클
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, oppoLoc);
		// Camera Shake
		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraShake(GrassCameraShakeFactory);
		//자속보정 계산
		if (this->pokemonType == Type::Grass)
		{
			sameType = 1.5f;
		}
		else
		{
			sameType = 1.f;
		}

		//스킬 위력에 따른 데미지 계산, 가지찌르기(위력 : 50/ 명중률 : 100)
		AttackDamage(50.f, OwnedTrainer->oppoTrainer->CurrentPokemon);
		break;
	case ESkill::SkillNormalTackle:
		//몸통박치기 - 염버니
		sameType = 1.f;

		//스킬 위력에 따른 데미지 계산, 몸통박치기(위력 : 40/ 명중률 : 100)
		AttackDamage(40, OwnedTrainer->oppoTrainer->CurrentPokemon);
		break;
	case ESkill::SkillNormalPound:
		//막치기 - 울머기
		sameType = 1.f;

		//스킬 위력에 따른 데미지 계산, 막치기(위력 : 40/ 명중률 : 100)
		AttackDamage(40.f, OwnedTrainer->oppoTrainer->CurrentPokemon);
		break;
	case ESkill::SkillNormalScratch:
		//할퀴기 - 흥나숭
		sameType = 1.f;

		//스킬 위력에 따른 데미지 계산, 할퀴기(위력 : 40/ 명중률 : 100)
		AttackDamage(40.f, OwnedTrainer->oppoTrainer->CurrentPokemon);
		break;
	case ESkill::SkillNormalStateChange_AttackPower:
		//상태변화1

		//상대방의 공격력 낮추기
		AttackPower(OwnedTrainer->oppoTrainer->CurrentPokemon);
		break;
	case ESkill::SkillNormalStateChange_DefencePower:
		//상태변화2

		//상대방의 방어력 낮추기
		DefencePower(OwnedTrainer->oppoTrainer->CurrentPokemon);
		break;
	}*/
	if (HasAuthority())
	{
		//ServerSkill(Skill, myLoc, oppoLoc);
		MultiSkill(Skill, myLoc, oppoLoc);
	}
	else
	{
		ServerSkill_Implementation(Skill, myLoc, oppoLoc);
	}
}

void APokemon::MultiSkill_Implementation(ESkill skill, FVector _myLoc, FVector _oppoLoc)
{
	switch (skill)
	{
	case ESkill::SkillWater:
		// 물대포 파티클
		if (WaterThrowParticle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), WaterThrowParticle, _myLoc, FRotator(GetActorForwardVector().Y * 90, GetActorForwardVector().Z * 90, GetActorForwardVector().X * 90)/*, FVector(0.5f, 0.5f, 1.0f)*/);


			// 1초 뒤에 실행
			GetWorldTimerManager().SetTimer(handle, [&]()
				{
					// 스플래시 파티클
					if (WaterHitParticle && WaterCameraShakeFactory)
					{
						UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), WaterHitParticle, _oppoLoc);
						// 카메라 쉐이크
						UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraShake(WaterCameraShakeFactory);
					}
				}, 1.f, false);
		}
		break;
	case ESkill::SkillFire:
		GetWorldTimerManager().SetTimer(handle, [&]()
			{
				FVector Loc = FMath::Lerp(_myLoc, _oppoLoc, alpha);
				// Shoot 파티클
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FireThrowParticle, Loc);
				alpha += 0.1f;
				if (alpha >= 1.0f)
				{
					alpha = 0.f;
					// Hit 파티클
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FireHitParticle, _oppoLoc);
					// Camera Shake
					UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraShake(WaterCameraShakeFactory);
					GetWorldTimerManager().ClearTimer(handle);
				}
			}, 0.1f, true);
		break;
	case ESkill::SkillGrass:
		// Hit 파티클
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), GrassHitParticle, _oppoLoc);
		// Camera Shake
		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraShake(GrassCameraShakeFactory);
		break;
	case ESkill::SkillNormalTackle:
		break;
	case ESkill::SkillNormalPound:
		break;
	case ESkill::SkillNormalScratch:
		break;
	case ESkill::SkillNormalStateChange_AttackPower:
		break;
	case ESkill::SkillNormalStateChange_DefencePower:
		break;
	}
}

void APokemon::ServerSkill_Implementation(ESkill skill, FVector _myloc, FVector _oppoloc)
{
	UE_LOG(LogTemp, Warning, TEXT("ill kill u"));
	MultiSkill_Implementation(skill, _myloc, _oppoloc);

}

//--------------------------------포켓몬 공격력------------------------------
int32 attackDamage;
float _power;
int32 APokemon::AttackDamage(float power, APokemon* otherPokemon)
{
	_power = power;
	//자속보정
	//사용하는 기술의 타입과 사용하는 포켓몬의 타입이 일치하면 1.5를 대입.

	//--------------------------타입상성
	//나 : 불타입
	if(this->pokemonType == Type::Fire)
	{
		switch (otherPokemon->pokemonType)
		{
			case Type::Fire:
				typecompat1 = 1.f;	typecompat2 = 1.f;
				break;
			case Type::Water:
				typecompat1 = 0.5f;	typecompat2 = 0.5f;
				break;
			case Type::Grass:
				typecompat1 = 1.5f;	typecompat2 = 1.5f;
				break;
			default:
				break;
		}
	}
	//나 : 물타입
	else if(this->pokemonType == Type::Water)
	{
		switch (otherPokemon->pokemonType)
		{
		case Type::Fire:
			typecompat1 = 1.5f;	typecompat2 = 1.5f;
			break;
		case Type::Water:
			typecompat1 = 1.f;	typecompat2 = 1.f;
			break;
		case Type::Grass:
			typecompat1 = 0.5f;	typecompat2 = 0.5f;
			break;
		default:
			break;
		}
	}
	//나 : 풀타입
	else if (this->pokemonType == Type::Grass)
	{
		switch (otherPokemon->pokemonType)
		{
		case Type::Fire:
			typecompat1 = 0.5f;	typecompat2 = 0.5f;
			break;
		case Type::Water:
			typecompat1 = 1.5f;	typecompat2 = 1.5f;
			break;
		case Type::Grass:
			typecompat1 = 1.f;	typecompat2 = 1.f;
			break;
		default:
			break;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("??"));
	}
	//--------------------------타입상성

	int32 RandomNumber;
	RandomNumber = FMath::RandRange(85, 100);
	UE_LOG(LogTemp, Warning, TEXT("Random : %d"), RandomNumber);

	//(데미지 = (위력 × 공격 × (레벨 × [[급소]] × 2 ÷ 5 + 2 ) ÷ 방어 ÷ 50 + 2 ) × [[자속 보정]] × 타입상성1 × 타입상성2 × 랜덤수/255)
	attackDamage = static_cast<int32>((_power * OwnedTrainer->CurrentPokemon->pokemonAttack * (35 * 1 * 2 / 5 + 2) / OwnedTrainer->oppoTrainer->CurrentPokemon->pokemonDefense / 50 + 2 ) * sameType * typecompat1 * typecompat2 * RandomNumber / 255);

	otherPokemon->pokemonCurHealth = otherPokemon->pokemonCurHealth - attackDamage;

	// int32 otherHP = otherPokemon->pokemonCurHealth;
	UE_LOG(LogTemp, Warning, TEXT("Power: %f, OtherPokeAttacked: %d"), _power, otherPokemon->pokemonCurHealth - attackDamage);

	return attackDamage;
}
//----------------------------포켓몬 상태변화---------------------------
void APokemon::AttackPower(APokemon* otherPokemon)
{
	//상대방의 공격력 낮추기
	
}

void APokemon::DefencePower(APokemon* otherPokemon)
{
	//상대방의 공격력 낮추기
}

void APokemon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APokemon, OwnedTrainer);
	DOREPLIFETIME(APokemon, myLoc);
	DOREPLIFETIME(APokemon, oppoLoc);

}
