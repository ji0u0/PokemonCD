// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyServerWidget.h"

#include "PokemonCDGameInstance.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void ULobbyServerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CreateSessionButton->OnClicked.AddDynamic(this, &ULobbyServerWidget::CreateSession);
	JoinSessionButton->OnClicked.AddDynamic(this, &ULobbyServerWidget::JoinSession);


}

void ULobbyServerWidget::CreateSession()
{
	auto PokemonCDGameInstance = Cast<UPokemonCDGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	PokemonCDGameInstance->CreateSession();
	
}

void ULobbyServerWidget::JoinSession()
{
	auto PokemonCDGameInstance = Cast<UPokemonCDGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (PokemonCDGameInstance)
	{
		PokemonCDGameInstance->JoinSession();
	}
}
