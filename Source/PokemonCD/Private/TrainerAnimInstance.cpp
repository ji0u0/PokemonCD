// Fill out your copyright notice in the Description page of Project Settings.


#include "TrainerAnimInstance.h"

#include "Trainer.h"

void UTrainerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	//Ʈ���̳ʸ� ����ϰ� �ʹ�
	trainer = Cast<ATrainer>(GetOwningActor());
}

void UTrainerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if(nullptr == trainer) return;

	isHasBall = trainer->isAttachBall ;
	
}

void UTrainerAnimInstance::AnimNotify_ThrowBall()
{
	if(isHasBall)
	{
		trainer->DetachBall();
	}
}

void UTrainerAnimInstance::AnimNotify_EndThrowBall()
{
	isHasBall = false;
}
