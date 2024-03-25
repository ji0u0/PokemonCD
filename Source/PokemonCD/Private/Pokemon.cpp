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
	NormalHitParticle = LoadObject<UParticleSystem>(nullptr, TEXT("/Game/JIU/Particle/P_ky_hit1.P_ky_hit1"));
	NormalChangeParticle = LoadObject<UParticleSystem>(nullptr, TEXT("/Game/JIU/Particle/P_ky_magicCircle1.P_ky_magicCircle1"));

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
}

// Called to bind functionality to input
void APokemon::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APokemon::OnRep_SetHealthBar()
{
	if (!OwnedTrainer)	return;
	if (!OwnedTrainer->oppoTrainer)	return;
	if (!OwnedTrainer->oppoTrainer->CurrentPokemon)	return;

	ATrainerPlayerController* myController = OwnedTrainer->GetController<ATrainerPlayerController>();
	ATrainerPlayerController* oppoController = OwnedTrainer->oppoTrainer->GetController<ATrainerPlayerController>();

	if (myController)
	{
		if (myController->MainWidget)
		{
			myController->MainWidget->SetStatus();
		}
	}
	if (oppoController)
	{
		if (oppoController->MainWidget)
		{
			oppoController->MainWidget->SetStatus();
		}
	}

	// OwnedTrainer->oppoTrainer->CurrentPokemon->StatusWidget->DamagedBar();
}


void APokemon::Skill(ESkill Skill)
{
	myLoc = GetActorLocation();
	oppoLoc = OwnedTrainer->oppoTrainer->CurrentPokemon->GetActorLocation();

	/*switch (Skill)
	{
	case ESkill::SkillWater:
		// ������ ��ƼŬ
		ThrowParticle = LoadObject<UParticleSystem>(nullptr, TEXT("/Game/JIU/Particle/P_Waterthrower.P_Waterthrower"));
		if (ThrowParticle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ThrowParticle, myLoc, GetActorForwardVector().Rotation()/*, FVector(0.5f, 0.5f, 1.0f)#1#);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ThrowParticle, myLoc, GetActorRightVector().Rotation()/*, FVector(0.5f, 0.5f, 1.0f)#1#);
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

		//��ų ���¿� ���� ������ ���, ������(���� : 50/ ���߷� : 100)
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
		//��ų ���¿� ���� ������ ���, �Ҳɼ���(���� : 50/ ���߷� : 100)
		AttackDamage(50.f, OwnedTrainer->oppoTrainer->CurrentPokemon);
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

		//��ų ���¿� ���� ������ ���, �������(���� : 50/ ���߷� : 100)
		AttackDamage(50.f, OwnedTrainer->oppoTrainer->CurrentPokemon);
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
		AttackDamage(40.f, OwnedTrainer->oppoTrainer->CurrentPokemon);
		break;
	case ESkill::SkillNormalScratch:
		//������ - �ﳪ��
		sameType = 1.f;

		//��ų ���¿� ���� ������ ���, ������(���� : 40/ ���߷� : 100)
		AttackDamage(40.f, OwnedTrainer->oppoTrainer->CurrentPokemon);
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
	}*/

	ServerSkill(Skill, myLoc, oppoLoc);

}

void APokemon::MultiSkill_Implementation(ESkill skill, FVector _myLoc, FVector _oppoLoc)
{
	switch (skill)
	{
	case ESkill::SkillWater:
		// ������ ��ƼŬ
		if (WaterThrowParticle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), WaterThrowParticle, myLoc, FRotator(GetActorForwardVector().Y * 90, GetActorForwardVector().Z * 90, GetActorForwardVector().X * 90));
			// 1�� �ڿ� ����
			GetWorldTimerManager().SetTimer(handle, [&]()
				{
					// ���÷��� ��ƼŬ
					if (WaterHitParticle && WaterCameraShakeFactory)
					{
						UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), WaterHitParticle, oppoLoc);
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

		//��ų ���¿� ���� ������ ���, ������(���� : 50/ ���߷� : 100)
		ServerAttackDamage(50.f, OwnedTrainer->oppoTrainer->CurrentPokemon);

		break;
	case ESkill::SkillFire:
		if (FireThrowParticle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FireThrowParticle, _myLoc);
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
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FireThrowParticle, Loc);
				alpha += 0.1f;
				if (alpha >= 1.0f)
				{
					alpha = 0.f;
					// Hit ��ƼŬ
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FireHitParticle, oppoLoc);
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
		//��ų ���¿� ���� ������ ���, �Ҳɼ���(���� : 50/ ���߷� : 100)
		ServerAttackDamage(50.f, OwnedTrainer->oppoTrainer->CurrentPokemon);
		break;
	case ESkill::SkillGrass:
		// Hit ��ƼŬ
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), GrassHitParticle, oppoLoc);
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

		//��ų ���¿� ���� ������ ���, �������(���� : 50/ ���߷� : 100)
		ServerAttackDamage(50.f, OwnedTrainer->oppoTrainer->CurrentPokemon);
		break;
	case ESkill::SkillNormalTackle:
		//�����ġ�� - ������
		/*// Hit ��ƼŬ
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), NormalHitParticle, oppoLoc + FVector(0, 0, 50.f));
		// Camera Shake
		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraShake(WaterCameraShakeFactory);*/

		// 1�� �ڿ� ����
		GetWorldTimerManager().SetTimer(handle, [&]()
			{
				// Hit ��ƼŬ
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), NormalHitParticle, oppoLoc + FVector(0, 0, 50.f));
				// Camera Shake
				UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraShake(WaterCameraShakeFactory);
			}, 1.f, false);

		sameType = 1.f;

		//��ų ���¿� ���� ������ ���, �����ġ��(���� : 40/ ���߷� : 100)
		ServerAttackDamage(40, OwnedTrainer->oppoTrainer->CurrentPokemon);
		break;
	case ESkill::SkillNormalPound:
		//��ġ�� - ��ӱ�
		// Hit ��ƼŬ
		GetWorldTimerManager().SetTimer(handle, [&]()
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), NormalHitParticle, oppoLoc);
				// Camera Shake
				UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraShake(WaterCameraShakeFactory);
			}, 1.f, false);
		sameType = 1.f;

		//��ų ���¿� ���� ������ ���, ��ġ��(���� : 40/ ���߷� : 100)
		ServerAttackDamage(40.f, OwnedTrainer->oppoTrainer->CurrentPokemon);
		break;
	case ESkill::SkillNormalScratch:
		//������ - �ﳪ��
		GetWorldTimerManager().SetTimer(handle, [&]()
			{
				// Hit ��ƼŬ
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), NormalHitParticle, oppoLoc);
				// Camera Shake
				UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraShake(WaterCameraShakeFactory);
			}, 1.f, false);
		sameType = 1.f;

		//��ų ���¿� ���� ������ ���, ������(���� : 40/ ���߷� : 100)
		ServerAttackDamage(40.f, OwnedTrainer->oppoTrainer->CurrentPokemon);
		break;
	case ESkill::SkillNormalStateChange_AttackPower:
		//���º�ȭ1
		// Hit ��ƼŬ
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), NormalChangeParticle, oppoLoc + FVector(0.f, 0.f, 100.f), FRotator(180.f, 0.f, 0.f));
		//������ ���ݷ� ���߱�
		AttackPower(OwnedTrainer->oppoTrainer->CurrentPokemon);
		break;
	case ESkill::SkillNormalStateChange_DefencePower:
		//���º�ȭ2

		// Hit ��ƼŬ
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), NormalChangeParticle, oppoLoc + FVector(0.f, 0.f, 100.f), FRotator(180.f, 0.f, 0.f));
		//������ ���� ���߱�
		DefencePower(OwnedTrainer->oppoTrainer->CurrentPokemon);
		break;
	}
}

void APokemon::ServerSkill_Implementation(ESkill skill, FVector _myloc, FVector _oppoloc)
{
	MultiSkill_Implementation(skill, _myloc, _oppoloc);

}

//--------------------------------���ϸ� ���ݷ�------------------------------
/*int32 attackDamage;
float _power;*/
float APokemon::AttackDamage(float power, APokemon* otherPokemon)
{
	// _power = power;
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

	float attackDamage;
	int32 RandomNumber;
	RandomNumber = FMath::RandRange(85, 100);
	UE_LOG(LogTemp, Warning, TEXT("Random : %d"), RandomNumber);

	//(������ = (���� �� ���� �� (���� �� [[�޼�]] �� 2 �� 5 + 2 ) �� ��� �� 50 + 2 ) �� [[�ڼ� ����]] �� Ÿ�Ի�1 �� Ÿ�Ի�2 �� ������/255)
	attackDamage = /*static_cast<int32>*/((power * OwnedTrainer->CurrentPokemon->pokemonAttack * (35 * 1 * 2 / 5 + 2) / OwnedTrainer->oppoTrainer->CurrentPokemon->pokemonDefense / 50 + 2 ) * sameType * typecompat1 * typecompat2 * RandomNumber / 255);

	otherPokemon->pokemonCurHealth = otherPokemon->pokemonCurHealth - attackDamage;

	// int32 otherHP = otherPokemon->pokemonCurHealth;
	UE_LOG(LogTemp, Warning, TEXT("Power: %f, ATKDamage: %f, OppoAfterHP: %f"), power, attackDamage ,otherPokemon->pokemonCurHealth);

	return attackDamage;
}

void APokemon::MultiAttackDamage_Implementation(float power, APokemon* otherPokemon)
{
	// AttackDamage( power,  otherPokemon);
}

void APokemon::ServerAttackDamage_Implementation(float power, APokemon* otherPokemon)
{
	AttackDamage(power, otherPokemon);
	OnRep_SetHealthBar();
}

//----------------------------���ϸ� ���º�ȭ---------------------------
void APokemon::AttackPower(APokemon* otherPokemon)
{
	//������ ���ݷ� ���߱�
	otherPokemon->pokemonAttack = otherPokemon->pokemonAttack * 2 / 3;
	UE_LOG(LogTemp, Warning, TEXT("OtherPokeAtkPower: %f"), otherPokemon->pokemonAttack);
}

void APokemon::ServerAttackPower_Implementation(APokemon* otherPokemon)
{
	AttackPower(otherPokemon);
}

void APokemon::DefencePower(APokemon* otherPokemon)
{
	//������ ���� ���߱�
	otherPokemon->pokemonDefense = otherPokemon->pokemonDefense * 2 / 3;
	UE_LOG(LogTemp, Warning, TEXT("OtherPokeDefencePower: %f"), otherPokemon->pokemonDefense);
}

void APokemon::ServerDefencePower_Implementation(APokemon* otherPokemon)
{
	DefencePower(otherPokemon);
}

void APokemon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APokemon, OwnedTrainer);
	DOREPLIFETIME(APokemon, myLoc);
	DOREPLIFETIME(APokemon, oppoLoc);
	DOREPLIFETIME(APokemon, pokemonCurHealth);
	DOREPLIFETIME(APokemon, pokemonAttack);
	DOREPLIFETIME(APokemon, pokemonDefense);
}
