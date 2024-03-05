// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyServerWidget.h"

#include "LobyGameMode.h"
#include "PokemonCDGameInstance.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void ULobbyServerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CreateSessionButton->OnClicked.AddDynamic(this, &ULobbyServerWidget::CreateSession);
	JoinSessionButton->OnClicked.AddDynamic(this, &ULobbyServerWidget::JoinSession);
	BattleStartButton->OnClicked.AddDynamic(this, &ULobbyServerWidget::OpenBattleLevel);
	GameInstance = Cast<UPokemonCDGameInstance>(GetGameInstance());
	if(GameInstance)
	{
		UpdatePlayerCount(GameInstance->GetNumberPlayers());
	}
	GameMode = Cast<ALobyGameMode>(GetWorld()->GetAuthGameMode());
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
	if(GameMode)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT(" CreateSession")); // 화면출력
		GameMode->TravelLevel();
	}
}

void ULobbyServerWidget::UpdatePlayerCount(int32 PlayerCount)
{
	if (WatingPlayerText)
	{
		WatingPlayerText->SetText(FText::FromString(FString::Printf(TEXT("플레이어 입장 대기중...: (%d/2)"), PlayerCount)));
	}
}
