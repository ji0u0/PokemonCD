// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetChoosePokemon.h"
#include "PokemonGameMode.h"
#include "Trainer.h"
#include "PokemonWater.h"
#include "Components/Button.h"

void UWidgetChoosePokemon::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Rabifoot->OnClicked.AddDynamic(this, &UWidgetChoosePokemon::ChooseRabifoot);
	Button_Sobble->OnClicked.AddDynamic(this, &UWidgetChoosePokemon::ChooseSobble);
	Button_Grookey->OnClicked.AddDynamic(this, &UWidgetChoosePokemon::ChooseGrookey);

	undoButton->OnClicked.AddDynamic(this, &UWidgetChoosePokemon::UndoSelect);
	completeButton->OnClicked.AddDynamic(this, &UWidgetChoosePokemon::CompleteUI);
}


void UWidgetChoosePokemon::ChooseRabifoot()
{
	trainer->SetCurrentPokemon(EPokemonList::Rabifoot);
}

void UWidgetChoosePokemon::ChooseSobble()
{
	trainer->SetCurrentPokemon(EPokemonList::Sobble);
}

void UWidgetChoosePokemon::ChooseGrookey()
{
	trainer->SetCurrentPokemon(EPokemonList::Grookey);
}

void UWidgetChoosePokemon::SelectedPokemon()
{
	trainer->SpawnPokemon();
}

void UWidgetChoosePokemon::UndoSelect()
{
	/*if (thirdFactory != nullptr)		thirdFactory = nullptr;
	else if (secondFactory != nullptr)	secondFactory = nullptr;
	else if (firstFactory != nullptr)	firstFactory = nullptr;*/
	trainer->currentPokemon = nullptr;
}


void UWidgetChoosePokemon::CompleteUI()
{
	// trainer -> pokemon 积己
	//if(firstFactory)
	//{
	//	trainer->firstPokemon = GetWorld()->SpawnActor<APokemon>(firstFactory, firstLoc, FRotator::ZeroRotator);
	//	trainer->firstPokemon->OwnedTrainer = trainer;
	//}
	//if (secondFactory)
	//{
	//	trainer->secondPokemon = GetWorld()->SpawnActor<APokemon>(secondFactory, secondLoc, FRotator::ZeroRotator);
	//	trainer->secondPokemon->OwnedTrainer = trainer;
	//}
	//if (thirdFactory)
	//{
	//trainer->thirdPokemon = GetWorld()->SpawnActor<APokemon>(thirdFactory, thirdLoc, FRotator::ZeroRotator);
	//trainer->thirdPokemon->OwnedTrainer = trainer;
	//}

	//// Possess Player Controller
	//APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	//PlayerController->Possess(trainer);

	// 困连 (肯傈) 昏力
	this->SetVisibility(ESlateVisibility::Hidden);
	if(trainer==nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("trainer null"))
		return;
	}
	trainer->CompleteChoose();
}

