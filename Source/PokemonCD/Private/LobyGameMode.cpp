// Fill out your copyright notice in the Description page of Project Settings.


#include "LobyGameMode.h"

#include "LobbyServerWidget.h"
#include "Blueprint/UserWidget.h"

void ALobyGameMode::BeginPlay()
{
	Super::BeginPlay();

	LobbyServerWidget = CreateWidget<ULobbyServerWidget>(GetWorld(), LobbyServerWidgetTemplate);
	LobbyServerWidget->AddToViewport();
}
