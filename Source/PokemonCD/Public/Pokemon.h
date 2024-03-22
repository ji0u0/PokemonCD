// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Pokemon.generated.h"

UENUM(BlueprintType)
enum class Type : uint8
{
	Normal UMETA(DisplayName = "Nrass"),
	Water UMETA(DisplayName = "Water"),
	Fire UMETA(DisplayName = "Fire"),
	Grass UMETA(DisplayName = "Grass")
};

UENUM(BlueprintType)
enum class ESkill : uint8
{
	SkillNormalTackle UMETA(DisplayName = "NormalTackle"),	//�����ġ�� - ������
	SkillNormalPound UMETA(DisplayName = "NormalPound"),	//��ġ�� - ��ӱ�
	SkillNormalScratch UMETA(DisplayName = "NormalScratch"),	//������ - �ﳪ��
	SkillNormalStateChange_AttackPower UMETA(DisplayName = "SkillNormalStateChange_AttackPower"),	//���º�ȭ1
	SkillNormalStateChange_DefencePower UMETA(DisplayName = "SkillNormalStateChange_DefencePower"),	//���º�ȭ2
	SkillWater UMETA(DisplayName = "WaterGun"),
	SkillFire UMETA(DisplayName = "Ember"),
	SkillGrass UMETA(DisplayName = "LeafStorm")
};

UCLASS()
class POKEMONCD_API APokemon : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APokemon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float timeDeltaTime;

	UPROPERTY(Replicated, EditDefaultsOnly)
	class ATrainer* OwnedTrainer;

	///// status /////
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FString pokemonName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	Type pokemonType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int pokemonMaxHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int pokemonCurHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float pokemonAttack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float pokemonDefense;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float pokemonSpeed;

	///// Skill /////
	ESkill firstSkill = ESkill::SkillWater;	//Ÿ�Խ�ų
	ESkill secondSkill = ESkill::SkillFire;	//�븻������ų
	ESkill thirdSkill = ESkill::SkillGrass;	//�븻���º�ȯ��ų1
	ESkill fourthSkill = ESkill::SkillGrass;	//�븻���º�ȯ��ų2

	UFUNCTION()
	void Skill(ESkill Skill);

	virtual void PlayFirstSkillAnim() {};
	virtual void PlaySecondSkillAnim() {};
	virtual void PlayThirdSkillAnim() {};
	virtual void PlayFourthSkillAnim() {};

	// Particle
	UParticleSystem* ThrowParticle;

	UParticleSystem* HitParticle;

	FVector myLoc;

	FVector oppoLoc;

	FTimerHandle handle;

	float alpha = 0.f;

	// Camera Shake -> ���ϸ��� ����� �� Factory�� ä�� ��
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCameraShakeBase> WaterCameraShakeFactory;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCameraShakeBase> GrassCameraShakeFactory;

	//--------------------------------���ϸ� ���ݷ�------------------------------
	int32 AttackDamage(float power, APokemon* otherPokemon);

	float typecompat1;
	float typecompat2;
	float sameType;	//�ڼӺ���

	//----------------------------���ϸ� ���º�ȭ---------------------------
	void AttackPower(APokemon* otherPokemon);	//���ݷº�ȭ
	void DefencePower(APokemon* otherPokemon);	//���º�ȭ
};
