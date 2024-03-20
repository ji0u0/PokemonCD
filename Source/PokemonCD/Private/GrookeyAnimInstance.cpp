// Fill out your copyright notice in the Description page of Project Settings.


#include "GrookeyAnimInstance.h"

void UGrookeyAnimInstance::PlayScorbunnyAttackMontage(float playTimes)
{
	if (nullptr == GrookeyAttack) return;
	Montage_Play(GrookeyAttack, 1.f, EMontagePlayReturnType::MontageLength, playTimes);
}
