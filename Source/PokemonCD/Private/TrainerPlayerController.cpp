// Fill out your copyright notice in the Description page of Project Settings.


#include "TrainerPlayerController.h"

#include "Pokemon.h"
#include "Trainer.h"
#include "WidgetChoosePokemon.h"
#include "WidgetMain.h"
#include "WidgetSkill.h"
#include "Blueprint/UserWidget.h"
#include "Net/UnrealNetwork.h"


void ATrainerPlayerController::CreatePokemonWidget()
{
	PokemonWidget = CreateWidget<UWidgetChoosePokemon>(GetWorld(), PokemonTemplate);
	PokemonWidget->AddToViewport(0);

	PokemonWidget->trainer = Cast<ATrainer>(GetPawn());
	PokemonWidget->_PlayerController = this;
	PokemonWidget->pc = this;
	SetVisiblePokemonWidget(true);
}

void ATrainerPlayerController::SetVisiblePokemonWidget(bool bVisible)
{
	if (bVisible)
	{
		PokemonWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		PokemonWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ATrainerPlayerController::CreateMainWidget()
{
	MainWidget = CreateWidget<UWidgetMain>(GetWorld(), MainWidgetTemplate);
	MainWidget->AddToViewport(0);
	SetVisibleMainWidget(false);
}

void ATrainerPlayerController::SetVisibleMainWidget(bool bVisible)
{
	if (bVisible)
	{
		MainWidget->SetVisibility(ESlateVisibility::Visible);
		MainWidget->SetStatus();
		// 상대 스테이터스도 추가하기
	}
	else
	{
		MainWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ATrainerPlayerController::CreateSkillWidget()
{
	SkillWidget = CreateWidget<UWidgetSkill>(GetWorld(), SkillWidgetTemplate);
	SkillWidget->AddToViewport(0);
	SetVisibleSkillWidget(false);
}

void ATrainerPlayerController::SetVisibleSkillWidget(bool bVisible)
{
	if (bVisible)
	{
		SkillWidget->SetVisibility(ESlateVisibility::Visible);
		if (auto poke = Cast<ATrainer>(GetPawn())->CurrentPokemon)
		{
			SkillWidget->SetSkillName(poke);
		}
	}
	else
	{
		SkillWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ATrainerPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATrainerPlayerController, Pokemon);
}
