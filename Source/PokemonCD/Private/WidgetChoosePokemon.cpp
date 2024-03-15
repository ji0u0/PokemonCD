// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetChoosePokemon.h"
#include "PokemonGameMode.h"
#include "Trainer.h"
#include "PokemonWater.h"
#include "TrainerPlayerController.h"
#include "Components/Button.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"

void UWidgetChoosePokemon::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Rabifoot->OnClicked.AddDynamic(this, &UWidgetChoosePokemon::ChooseRabifoot);
	Button_Sobble->OnClicked.AddDynamic(this, &UWidgetChoosePokemon::ChooseSobble);
	Button_Grookey->OnClicked.AddDynamic(this, &UWidgetChoosePokemon::ChooseGrookey);

	undoButton->OnClicked.AddDynamic(this, &UWidgetChoosePokemon::UndoSelect);
	completeButton->OnClicked.AddDynamic(this, &UWidgetChoosePokemon::CompleteUI);

	//_PlayerController = Cast<ATrainerPlayerController>(GetWorld()->GetFirstPlayerController());

}


void UWidgetChoosePokemon::ChooseRabifoot()
{
	//if (_PlayerController->IsLocalPlayerController())
	trainer->SetPokemon(EPokemonList::RABIFOOT);
}

void UWidgetChoosePokemon::ChooseSobble()
{
	//if (_PlayerController->IsLocalPlayerController())
	trainer->SetPokemon(EPokemonList::SOBBLE);
}

void UWidgetChoosePokemon::ChooseGrookey()
{
	//if (_PlayerController->IsLocalPlayerController())
	trainer->SetPokemon(EPokemonList::GROOKEY);
}

void UWidgetChoosePokemon::SelectedPokemon()
{
	//trainer->SpawnPokemon();
}

void UWidgetChoosePokemon::UndoSelect()
{
	/*if (thirdFactory != nullptr)		thirdFactory = nullptr;
	else if (secondFactory != nullptr)	secondFactory = nullptr;
	else if (firstFactory != nullptr)	firstFactory = nullptr;*/
	//trainer->currentPokemon = nullptr;
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

	if (trainer == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("trainer null"));
		return;
	}

	trainer->CompleteChoose();
	auto pc = GetWorld()->GetFirstPlayerController();
	FString localRole = UEnum::GetValueAsString(trainer->GetLocalRole());
	if (pc && trainer->IsLocallyControlled())
	{
		UE_LOG(LogTemp, Warning, TEXT("ServerSpawnPokemon call!!,    LocalRole : %s, %d"), *localRole, _PlayerController->Pokemon);

		//trainer->ServerSpawnPokemon(trainer->Pokemon);

#pragma region Original
		if (trainer->HasAuthority())
		{
			trainer->MultiSpawnPokemon(trainer->Pokemon);
			UE_LOG(LogTemp, Warning, TEXT("Authority spwawn 1"));
		}
		else
		{
			trainer->tmp();
			trainer->ServerSpawnPokemon(trainer->Pokemon);
			UE_LOG(LogTemp, Warning, TEXT("Autonomous spawn 2"));
		}
#pragma endregion
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ServerSpawnPokemon failed...,    LocalRole : %s"), *localRole);
	}
}

