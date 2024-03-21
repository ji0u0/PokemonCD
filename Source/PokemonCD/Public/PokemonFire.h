// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pokemon.h"
#include "PokemonFire.generated.h"

/**
 * 
 */
UCLASS()
class POKEMONCD_API APokemonFire : public APokemon
{
	GENERATED_BODY()
public:
	APokemonFire();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	// Components
	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* SkelMeshComp;

	// Skills
	UPROPERTY(BlueprintReadWrite)
	class USkillWater* waterSkill;

	//�ִϸ��̼�
	UFUNCTION()
	void AttackingAnim(float index);

	//�ִϸ��̼� ����
	virtual void PlayFirstSkillAnim() override;
	virtual void PlaySecondSkillAnim() override;
	virtual void PlayThirdSkillAnim() override;
	virtual void PlayFourthSkillAnim() override;

	//���� �ϱ�(���� ��� ���ϸ� hp�� �پ��� �Ѵ�
	UFUNCTION()
	void OnMyAttack(APokemon* otherpokemon);
};
