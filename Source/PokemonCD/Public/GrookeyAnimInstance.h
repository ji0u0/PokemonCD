// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GrookeyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class POKEMONCD_API UGrookeyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	class UAnimMontage* GrookeyAttack;
	void PlayScorbunnyAttackMontage(float playTimes);
};
