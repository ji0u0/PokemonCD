// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SobbleAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class POKEMONCD_API USobbleAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	class UAnimMontage* sobbleAttack;
	void PlaySobbleNomalAttackMontage(int32 playTime);

	/*UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float playRate;*/
};
