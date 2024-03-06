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
	//LobbyServerWidget = CreateWidget<ULobbyServerWidget>(GetWorld(), LobbyServerWidgetTemplate);
	//LobbyServerWidget->AddToViewport();
}

void ALobyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	

}

void ALobyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	
}

void ALobyGameMode::TravelLevel()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT(" Travel")); // 화면출력
	GetWorld()->ServerTravel("/Game/Maps/LV_Total.LV_Total?listen");
}

