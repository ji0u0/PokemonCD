// Fill out your copyright notice in the Description page of Project Settings.


#include "TrainerAnimInstance.h"

#include "Trainer.h"

void UTrainerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	//트레이너를 기억하고 싶다
	trainer = Cast<ATrainer>(GetOwningActor());
}

void UTrainerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if(nullptr == trainer) return;

	isHasBall = trainer->isAttachBall;
	
}

void UTrainerAnimInstance::PlayThrowMontage()
{
	if(nullptr == throwMontage) return;
	Montage_Play(throwMontage);
}

void UTrainerAnimInstance::AnimNotify_ThrowBall()
{
	trainer->DetachBall();
}

/*void UTrainerAnimInstance::AnimNotify_EndThrowBall()
{
	isHasBall = false;
}*/
