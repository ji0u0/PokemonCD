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

	//Ŭ���̾�Ʈ�� �������� ��Ÿ������? ����
	UFUNCTION(Server, Reliable)
	void ServerTrainerMontage();
	//������ Ŭ���̾�Ʈ���� ��Ÿ�� �����϶�� ��Ŵ
	UFUNCTION(NetMulticast, Reliable)
	void MultiTrainerMontage();

	/*UFUNCTION()
	void AnimNotify_EndThrowBall();*/

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
