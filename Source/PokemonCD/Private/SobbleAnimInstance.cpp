// Fill out your copyright notice in the Description page of Project Settings.

#include "SobbleAnimInstance.h"

void USobbleAnimInstance::PlaySobbleNomalAttackMontage(int32 playTime)
{
	if(nullptr == sobbleAttack) return;
	Montage_Play(sobbleAttack, 1.f, EMontagePlayReturnType::Duration, playTime);
}
