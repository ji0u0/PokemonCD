// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetChoosePokemon.h"

#include "Trainer.h"
#include "PokemonWater.h"
#include "Components/Button.h"

void UWidgetChoosePokemon::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Sobble->OnClicked.AddDynamic(this, &UWidgetChoosePokemon::ChooseSobble);
	undoButton->OnClicked.AddDynamic(this, &UWidgetChoosePokemon::UndoSelect);
	completeButton->OnClicked.AddDynamic(this, &UWidgetChoosePokemon::CompleteUI);
}

void UWidgetChoosePokemon::CompleteUI()
{
	// trainer 积己
	trainer = GetWorld()->SpawnActor<ATrainer>(trainerFactory, trainerLoc, trainerRot);

	// trainer -> pokemon 积己
	trainer->firstPokemon = GetWorld()->SpawnActor<APokemon>(firstFactory, firstLoc, FRotator::ZeroRotator);
	trainer->secondPokemon = GetWorld()->SpawnActor<APokemon>(secondFactory, secondLoc, FRotator::ZeroRotator);
	trainer->thirdPokemon = GetWorld()->SpawnActor<APokemon>(thirdFactory, thirdLoc, FRotator::ZeroRotator);

	// Possess Player Controller
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->Possess(trainer);

	// 困连 (肯傈) 昏力
	this->RemoveFromParent();
}

void UWidgetChoosePokemon::UndoSelect()
{
	if (thirdFactory != nullptr)		thirdFactory = nullptr;
	else if (secondFactory != nullptr)	secondFactory = nullptr;
	else if (firstFactory != nullptr)	firstFactory = nullptr;
}

void UWidgetChoosePokemon::ChooseSobble()
{
	if (firstFactory == nullptr)		firstFactory = sobbleFactory;
	else if (secondFactory == nullptr)	secondFactory = sobbleFactory;
	else if (thirdFactory == nullptr)	thirdFactory = sobbleFactory;
}
