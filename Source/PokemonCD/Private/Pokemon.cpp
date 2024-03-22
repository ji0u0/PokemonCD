// Fill out your copyright notice in the Description page of Project Settings.


#include "Pokemon.h"

#include "Trainer.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"


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
	//ó�� �¾���� ���� ü�� = maxü��
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

	switch (Skill)
	{
	case ESkill::SkillWater:
		// ������ ��ƼŬ
		ThrowParticle = LoadObject<UParticleSystem>(nullptr, TEXT("/Game/JIU/Particle/P_Waterthrower.P_Waterthrower"));
		if (ThrowParticle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ThrowParticle, myLoc, GetActorUpVector().Rotation(), FVector(0.5f, 0.5f, 1.0f));
			// 1�� �ڿ� ����
			GetWorldTimerManager().SetTimer(handle, [&]()
				{
					// ���÷��� ��ƼŬ
					HitParticle = LoadObject<UParticleSystem>(nullptr, TEXT("/Game/JIU/Particle/P_WaterExplosion.P_WaterExplosion"));
					if (HitParticle && WaterCameraShakeFactory)
					{
						UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, oppoLoc);
						// ī�޶� ����ũ
						UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraShake(WaterCameraShakeFactory);
					}
				}, 1.f, false);
		}
		//�ڼӺ��� ���
		if (this->pokemonType == Type::Water)
		{
			sameType = 1.5f;
		}
		else
		{
			sameType = 1.f;
		}

		//��ų ���¿� ���� ������ ���, ������(���� : 40/ ���߷� : 100)
		AttackDamage(50, OwnedTrainer->oppoTrainer->CurrentPokemon);

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
				// Shoot ��ƼŬ
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ThrowParticle, Loc);
				alpha += 0.1f;
				if (alpha >= 1.0f)
				{
					alpha = 0.f;
					HitParticle = LoadObject<UParticleSystem>(nullptr, TEXT("/Game/JIU/Particle/P_ky_waterBallHit.P_ky_waterBallHit"));
					// Hit ��ƼŬ
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, oppoLoc);
					// Camera Shake
					UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraShake(WaterCameraShakeFactory);
					GetWorldTimerManager().ClearTimer(handle);
				}
			}, 0.1f, true);

		//�ڼӺ��� ���
		if (this->pokemonType == Type::Fire)
		{
			sameType = 1.5f;
		}
		else
		{
			sameType = 1.f;
		}
		//��ų ���¿� ���� ������ ���, �Ҳɼ���(���� : 40/ ���߷� : 100)
		AttackDamage(50, OwnedTrainer->oppoTrainer->CurrentPokemon);
		break;
	case ESkill::SkillGrass:
		HitParticle = LoadObject<UParticleSystem>(nullptr, TEXT("/Game/JIU/Particle/P_ky_storm.P_ky_storm"));
		// Hit ��ƼŬ
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, oppoLoc);
		// Camera Shake
		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraShake(GrassCameraShakeFactory);
		//�ڼӺ��� ���
		if (this->pokemonType == Type::Grass)
		{
			sameType = 1.5f;
		}
		else
		{
			sameType = 1.f;
		}

		//��ų ���¿� ���� ������ ���, �������(���� : 40/ ���߷� : 100)
		AttackDamage(50, OwnedTrainer->oppoTrainer->CurrentPokemon);
		break;
	case ESkill::SkillNormalTackle:
		//�����ġ�� - ������
		sameType = 1.f;

		//��ų ���¿� ���� ������ ���, �����ġ��(���� : 40/ ���߷� : 100)
		AttackDamage(40, OwnedTrainer->oppoTrainer->CurrentPokemon);
		break;
	case ESkill::SkillNormalPound:
		//��ġ�� - ��ӱ�
		sameType = 1.f;

		//��ų ���¿� ���� ������ ���, ��ġ��(���� : 40/ ���߷� : 100)
		AttackDamage(40, OwnedTrainer->oppoTrainer->CurrentPokemon);
		break;
	case ESkill::SkillNormalScratch:
		//������ - �ﳪ��
		sameType = 1.f;

		//��ų ���¿� ���� ������ ���, ������(���� : 40/ ���߷� : 100)
		AttackDamage(40, OwnedTrainer->oppoTrainer->CurrentPokemon);
		break;
	case ESkill::SkillNormalStateChange_AttackPower:
		//���º�ȭ1

		//������ ���ݷ� ���߱�
		AttackPower(OwnedTrainer->oppoTrainer->CurrentPokemon);
		break;
	case ESkill::SkillNormalStateChange_DefencePower:
		//���º�ȭ2

		//������ ���� ���߱�
		DefencePower(OwnedTrainer->oppoTrainer->CurrentPokemon);
		break;
	}

}
//--------------------------------���ϸ� ���ݷ�------------------------------
int32 APokemon::AttackDamage(float power, APokemon* otherPokemon)
{
	int32 attackDamage;

	//�ڼӺ���
	//����ϴ� ����� Ÿ�԰� ����ϴ� ���ϸ��� Ÿ���� ��ġ�ϸ� 1.5�� ����.

	//--------------------------Ÿ�Ի�
	//�� : ��Ÿ��
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
	//�� : ��Ÿ��
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
	//�� : ǮŸ��
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
	//--------------------------Ÿ�Ի�

	float randomInt = FMath::RandRange(85, 100) / 255;

	//(������ = (���� �� ���� �� (���� �� [[�޼�]] �� 2 �� 5 + 2 ) �� ��� �� 50 + 2 ) �� [[�ڼ� ����]] �� Ÿ�Ի�1 �� Ÿ�Ի�2 �� ������/255)
	attackDamage = (power * pokemonAttack * (35 * 1 * 2 / 5 + 2) / otherPokemon->pokemonDefense / 50 + 2 ) * sameType * typecompat1 * typecompat2 * randomInt;

	otherPokemon->pokemonCurHealth = otherPokemon->pokemonCurHealth - attackDamage;

	// int32 otherHP = otherPokemon->pokemonCurHealth;
	UE_LOG(LogTemp, Warning, TEXT("Power: %f, OtherPokeAttacked: %d"), power, otherPokemon->pokemonCurHealth);

	return attackDamage;
}
//----------------------------���ϸ� ���º�ȭ---------------------------
void APokemon::AttackPower(APokemon* otherPokemon)
{
	//������ ���ݷ� ���߱�
}

void APokemon::DefencePower(APokemon* otherPokemon)
{
	//������ ���ݷ� ���߱�
}

void APokemon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APokemon, OwnedTrainer);
}
