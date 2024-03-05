// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyServerWidget.h"

#include "LobyGameMode.h"
#include "PokemonCDGameInstance.h"
#include "PokemonGameInstanceSubSystem.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void ULobbyServerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CreateSessionButton->OnClicked.AddDynamic(this, &ULobbyServerWidget::CreateSession);
	JoinSessionButton->OnClicked.AddDynamic(this, &ULobbyServerWidget::JoinSession);
	BattleStartButton->OnClicked.AddDynamic(this, &ULobbyServerWidget::OpenBattleLevel);
	PokemonGameInstanceSubSystem = GetGameInstance()->GetSubsystem<UPokemonGameInstanceSubSystem>();

	
	GameMode = Cast<ALobyGameMode>(GetWorld()->GetAuthGameMode());
}

void ULobbyServerWidget::CreateSession()
{
	if (PokemonGameInstanceSubSystem)
	{
		PokemonGameInstanceSubSystem->CreateSession(2, FString("MatchType"));
	}
}

void ULobbyServerWidget::JoinSession()
{
	if (PokemonGameInstanceSubSystem)
	{
		PokemonGameInstanceSubSystem->FindSession(30);
	}
}

void ULobbyServerWidget::OpenBattleLevel()
{
	if(GameMode)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT(" CreateSession")); // ȭ�����
		GameMode->TravelLevel();
	}
}

void ULobbyServerWidget::UpdatePlayerCount(int32 PlayerCount)
{
	if (WatingPlayerText)
	{
		WatingPlayerText->SetText(FText::FromString(FString::Printf(TEXT("�÷��̾� ���� �����...: (%d/2)"), PlayerCount)));
	}
}
