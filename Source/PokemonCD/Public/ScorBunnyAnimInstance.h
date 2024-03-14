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

	//������ ��Ÿ�԰���(�Ҳɼ���)
	UPROPERTY(EditDefaultsOnly)
	class UAnimMontage* scorbunnyTypeAttack;
	void PlayScorbunnyTypeAttackMontage();

	//������ �븻��������(�����ġ��)
	UPROPERTY(EditDefaultsOnly)
	class UAnimMontage* scorbunnyNomalAttack;
	void PlayScorbunnyNomalAttackMontage();

	UFUNCTION()
	void AnimNotify_EndAttack();

};
