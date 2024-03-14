// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ScorBunnyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class POKEMONCD_API UScorBunnyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;

	UPROPERTY()
	class APokemon* pokemon;

	UPROPERTY()
	class ATrainer* trainer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool isAttack;

	UPROPERTY()
	class UWidgetSkill* widgetSkill;

	//염버니 불타입공격(불꽃세례)
	UPROPERTY(EditDefaultsOnly)
	class UAnimMontage* scorbunnyAttack;
	void PlayScorbunnyTypeAttackMontage();

	//염버니 노말물리공격(몸통박치기)
	void PlayScorbunnyNomalAttackMontage();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float playRate;

	UFUNCTION()
	void AnimNotify_EndAttack();

};
