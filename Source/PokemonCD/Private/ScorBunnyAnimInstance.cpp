// Fill out your copyright notice in the Description page of Project Settings.


#include "ScorBunnyAnimInstance.h"

#include "Pokemon.h"
#include "Trainer.h"
#include "WidgetSkill.h"

void UScorBunnyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if(Cast<APokemon>(GetOwningActor()))
	{
		UE_LOG(LogTemp, Warning, TEXT("cast"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("cast fail"));
		return;
	}
	pokemon = Cast<APokemon>(GetOwningActor());
	trainer = Cast<ATrainer>(pokemon->OwnedTrainer);
	if(trainer)
	{
		widgetSkill = Cast<UWidgetSkill>(trainer->skillWidget);
	}

	//isAttack = widgetSkill->isFirstAttack;
}

void UScorBunnyAnimInstance::PlayScorbunnyTypeAttackMontage()
{
	if(nullptr == scorbunnyTypeAttack) return;
	Montage_Play(scorbunnyTypeAttack);
}

void UScorBunnyAnimInstance::PlayScorbunnyNomalAttackMontage()
{
	if(nullptr == scorbunnyNomalAttack) return;
	Montage_Play(scorbunnyNomalAttack);
}

void UScorBunnyAnimInstance::AnimNotify_EndAttack()
{
}
