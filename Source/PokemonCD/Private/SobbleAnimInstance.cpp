// Fill out your copyright notice in the Description page of Project Settings.

#include "SobbleAnimInstance.h"

void USobbleAnimInstance::PlaySobbleNomalAttackMontage(int32 playRate)
{
	if(nullptr == sobbleAttack) return;
	Montage_Play(sobbleAttack, playRate);
}
