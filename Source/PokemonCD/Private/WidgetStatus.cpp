// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetStatus.h"

#include "Trainer.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"

void UWidgetStatus::NativeConstruct()
{
	Super::NativeConstruct();
}

void UWidgetStatus::SetPokeballBox(ATrainer* trainer)
{
	int num = 6;

	if(trainer->firstPokemon)
	{
		normalBallImage = CreateWidget<UUserWidget>(GetWorld(), normalBallFactory);
		PokeballBox->AddChildToHorizontalBox(normalBallImage);
		num--;
	}
	if (trainer->secondPokemon)
	{
		normalBallImage = CreateWidget<UUserWidget>(GetWorld(), normalBallFactory);
		PokeballBox->AddChildToHorizontalBox(normalBallImage);
		num--;
	}
	if (trainer->secondPokemon)
	{
		normalBallImage = CreateWidget<UUserWidget>(GetWorld(), normalBallFactory);
		PokeballBox->AddChildToHorizontalBox(normalBallImage);
		num--;
	}
	for (num; num > 0; num--)
	{
		noneBallImage = CreateWidget<UUserWidget>(GetWorld(), noneBallFactory);
		PokeballBox->AddChildToHorizontalBox(noneBallImage);
	}
}
