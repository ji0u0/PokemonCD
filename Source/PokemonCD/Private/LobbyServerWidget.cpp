// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyServerWidget.h"

#include "PokemonCDGameInstance.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void ULobbyServerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CreateSessionButton->OnClicked.AddDynamic(this, &ULobbyServerWidget::CreateSession);
	JoinSessionButton->OnClicked.AddDynamic(this, &ULobbyServerWidget::JoinSession);
	GameInstance = Cast<UPokemonCDGameInstance>(GetGameInstance());
	if(GameInstance)
	{
		UpdatePlayerCount(GameInstance->GetNumberPlayers());
	}
}

void ULobbyServerWidget::CreateSession()
{
	if (GameInstance)
	{
		GameInstance->CreateSession();
	}
}

void ULobbyServerWidget::JoinSession()
{
	if (GameInstance)
	{
		GameInstance->JoinSession();
	}
}

void ULobbyServerWidget::OpenBattleLevel()
{

}

void ULobbyServerWidget::UpdatePlayerCount(int32 PlayerCount)
{
	if (WatingPlayerText)
	{
		WatingPlayerText->SetText(FText::FromString(FString::Printf(TEXT("플레이어 입장 대기중...: (%d/2)"), PlayerCount)));
	}
}
