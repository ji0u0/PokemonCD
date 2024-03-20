// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pokemon.h"
#include "PokemonGrass.generated.h"

/**
 * 
 */
UCLASS()
class POKEMONCD_API APokemonGrass : public APokemon
{
	GENERATED_BODY()
public:
	APokemonGrass();

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

	//애니메이션
	void AttackingAnim(int32 index);

	//애니메이션 실행
	virtual void PlayFirstSkillAnim() override;
	virtual void PlaySecondSkillAnim() override;
	virtual void PlayThirdSkillAnim() override;
	virtual void PlayFourthSkillAnim() override;

	//공격 하기(공격 대상 포켓몬 hp를 줄어들게 한다
	void OnMyAttack(APokemon* otherpokemon);
};
