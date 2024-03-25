// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetStatus.h"

#include "Pokemon.h"
#include "Trainer.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"

void UWidgetStatus::NativeConstruct()
{
	Super::NativeConstruct();
}

void UWidgetStatus::DamagedBar()
{
	HealthBar->SetPercent(OwnedPokemon->pokemonCurHealth/OwnedPokemon->pokemonMaxHealth);
}

//void UWidgetStatus::SetPokeballBox(ATrainer* trainer)
//{
//	int num = 6;
//
//	if(trainer->FirstPokemon)
//	{
//		normalBallImage = CreateWidget<UUserWidget>(GetWorld(), normalBallFactory);
//		PokeballBox->AddChildToHorizontalBox(normalBallImage);
//		num--;
//	}
//	if (trainer->SecondPokemon)
//	{
//		normalBallImage = CreateWidget<UUserWidget>(GetWorld(), normalBallFactory);
//		PokeballBox->AddChildToHorizontalBox(normalBallImage);
//		num--;
//	}
//	if (trainer->ThirdPokemon)
//	{
//		normalBallImage = CreateWidget<UUserWidget>(GetWorld(), normalBallFactory);
//		PokeballBox->AddChildToHorizontalBox(normalBallImage);
//		num--;
//	}
//	for (num; num > 0; num--)
//	{
//		noneBallImage = CreateWidget<UUserWidget>(GetWorld(), noneBallFactory);
//		PokeballBox->AddChildToHorizontalBox(noneBallImage);
//	}
//}
