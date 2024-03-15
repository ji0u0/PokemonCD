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

	UPROPERTY(EditDefaultsOnly)
	class UAnimMontage* throwMontage;

	UPROPERTY(EditDefaultsOnly)
	class UAnimMontage* CheeringMontage;

	void PlayThrowMontage();
	void PlayCheeringMontage();

	UFUNCTION()
	void AnimNotify_ThrowBall();

	//클라이언트는 서버에게 몽타주정보? 보냄
	UFUNCTION(Server, Reliable)
	void ServerTrainerMontage();
	//서버는 클라이언트에게 몽타주 실행하라고 시킴
	UFUNCTION(NetMulticast, Reliable)
	void MultiTrainerMontage();

	/*UFUNCTION()
	void AnimNotify_EndThrowBall();*/

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
