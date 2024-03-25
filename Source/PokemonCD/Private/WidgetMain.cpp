// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetMain.h"

#include "Pokemon.h"
#include "Trainer.h"
#include "WidgetStatus.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/CanvasPanel.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UWidgetMain::NativeConstruct()
{
	Super::NativeConstruct();

	// My Status �߰�
	myStatus = CreateWidget<UWidgetStatus>(GetWorld(), statusWidgetFactory);
	UCanvasPanelSlot* MyStatusSlot = MyStatusPanel->AddChildToCanvas(myStatus);
	MyStatusSlot->SetSize(FVector2D(360, 240));

	// Opponent Status �߰�
	oppoStatus = CreateWidget<UWidgetStatus>(GetWorld(), statusWidgetFactory);
	UCanvasPanelSlot* OpponentStatusSlot = OpponentStatusPanel->AddChildToCanvas(oppoStatus);
	OpponentStatusSlot->SetSize(FVector2D(360, 240));

	// �� Controller�� �����´�
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	//if (PlayerController) trainer = Cast<ATrainer>(PlayerController->GetPawn());

	//else UE_LOG(LogTemp, Warning, TEXT("No Controller"));
}

void UWidgetMain::SetStatus()
{
	APokemon* myPokemon = trainer->CurrentPokemon;
	APokemon* oppoPokemon = trainer->oppoTrainer->CurrentPokemon;

	if(!myPokemon || !oppoPokemon)
	{ return;}

	myStatus->OwnedPokemon = myPokemon;
	myPokemon->StatusWidget = myStatus;
	myStatus->PokemonName->SetText(FText::FromString(myPokemon->pokemonName));
	myStatus->HealthBar->SetPercent(myPokemon->pokemonCurHealth / myPokemon->pokemonMaxHealth);

	oppoStatus->OwnedPokemon = oppoPokemon;
	oppoPokemon->StatusWidget = oppoStatus;
	oppoStatus->PokemonName->SetText(FText::FromString(oppoPokemon->pokemonName));
	oppoStatus->HealthBar->SetPercent(oppoPokemon->pokemonCurHealth / oppoPokemon->pokemonMaxHealth);
}
