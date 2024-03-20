// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetChoosePokemon.h"
#include "PokemonGameMode.h"
#include "PokemonGameState.h"
#include "Trainer.h"
#include "PokemonWater.h"
#include "TrainerPlayerController.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"

void UWidgetChoosePokemon::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Rabifoot->OnClicked.AddDynamic(this, &UWidgetChoosePokemon::ChooseRabifoot);
	Button_Sobble->OnClicked.AddDynamic(this, &UWidgetChoosePokemon::ChooseSobble);
	Button_Grookey->OnClicked.AddDynamic(this, &UWidgetChoosePokemon::ChooseGrookey);

	undoButton->OnClicked.AddDynamic(this, &UWidgetChoosePokemon::UndoSelect);
	completeButton->OnClicked.AddDynamic(this, &UWidgetChoosePokemon::SelectComplete);

	//_PlayerController = Cast<ATrainerPlayerController>(GetWorld()->GetFirstPlayerController());
	
	GameState = GetWorld()->GetGameState<APokemonGameState>();
	if(GameState)
	{
		GameState->FOnMyPokemonChooseComplete.BindUObject(this, &UWidgetChoosePokemon::SpawnOrder);
	}
	
	
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


void UWidgetChoosePokemon::SelectComplete()
{
	if (trainer == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("trainer null"));
		return;
	}

	auto pc = GetWorld()->GetFirstPlayerController();
	FString localRole = UEnum::GetValueAsString(trainer->GetLocalRole());
	if (pc && trainer->IsLocallyControlled())
	{
		UE_LOG(LogTemp, Warning, TEXT("ServerSpawnPokemon call!!,    LocalRole : %s, %d"), *localRole, _PlayerController->Pokemon);
		
		if (trainer->HasAuthority())
		{
			ChooseCanvasSwitcher->SetActiveWidgetIndex(SWITCHER_INDEX_Wating);
			trainer->AuthorityCompleteChoose();
		}
		else
		{
			ChooseCanvasSwitcher->SetActiveWidgetIndex(SWITCHER_INDEX_Wating);
			trainer->AutonomousCompleteChoose();
		}
	}
}

void UWidgetChoosePokemon::SpawnOrder()
{
	auto pc = GetWorld()->GetFirstPlayerController();
	if (pc && trainer->IsLocallyControlled())
	{
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
		this->SetVisibility(ESlateVisibility::Hidden);
	}
}

