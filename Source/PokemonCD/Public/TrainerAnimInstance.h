// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TrainerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class POKEMONCD_API UTrainerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditDefaultsOnly)
	class ATrainer* trainer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool isHasBall;

	UFUNCTION()
	void AnimNotify_ThrowBall();

	UFUNCTION()
	void AnimNotify_EndThrowBall();
};
