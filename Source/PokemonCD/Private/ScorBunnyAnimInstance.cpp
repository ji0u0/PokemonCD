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
	playRate = 0;
	if(nullptr == scorbunnyAttack) return;
	Montage_Play(scorbunnyAttack, playRate);
}

void UScorBunnyAnimInstance::PlayScorbunnyNomalAttackMontage()
{
	playRate = 1;
	if(nullptr == scorbunnyAttack) return;
	Montage_Play(scorbunnyAttack, playRate);
}
