// Fill out your copyright notice in the Description page of Project Settings.


#include "LobyGameMode.h"

#include "LobbyServerWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"

ALobyGameMode::ALobyGameMode()
{
}

void ALobyGameMode::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<UPokemonCDGameInstance>(GetGameInstance());
	LobbyServerWidget = CreateWidget<ULobbyServerWidget>(GetWorld(), LobbyServerWidgetTemplate);
	LobbyServerWidget->AddToViewport();
}

void ALobyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	if(GameInstance)
	{
		GameInstance->UpdateNumPlayers(GameInstance->GetNumberPlayers() + 1);
	}

}

void ALobyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	if (GameInstance)
	{
		GameInstance->UpdateNumPlayers(GameInstance->GetNumberPlayers() - 1);
	}
}

