// Fill out your copyright notice in the Description page of Project Settings.

#include "SobbleAnimInstance.h"
void USobbleAnimInstance::PlaySobbleNomalAttackMontage()
{
	if(nullptr == sobbleAttack) return;
	playRate = 0;
	Montage_Play(sobbleAttack, playRate);
}
