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
	JoinServerButton->OnClicked.AddDynamic(this, &ULobbyServerWidget::JoinSession);
	ServerTravelButton->OnClicked.AddDynamic(this, &ULobbyServerWidget::ServerTravel);

	PokemonGameInstanceSubSystem = GetGameInstance()->GetSubsystem<UPokemonGameInstanceSubSystem>();
	GameInstance = Cast<UPokemonCDGameInstance>(GetWorld()->GetGameInstance());

	
	GameMode = Cast<ALobyGameMode>(GetWorld()->GetAuthGameMode());
}

void ULobbyServerWidget::CreateSession()
{
	/*if (PokemonGameInstanceSubSystem)
	{
		PokemonGameInstanceSubSystem->CreateSession(2, FString("MatchType"));
	}*/
	GameInstance->OpenLobby();
}

void ULobbyServerWidget::JoinSession()
{
	//if (GameMode)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT(" CreateSession")); // 화면출력
	//	GameMode->TravelLevel();
	//}
	GameInstance->CallOpenLevel("192.168.240.92");
}

void ULobbyServerWidget::ServerTravel()
{
	GameInstance->ServerTravel();
}

void ULobbyServerWidget::UpdatePlayerCount(int32 PlayerCount)
{
	if (WatingPlayerText)
	{
		WatingPlayerText->SetText(FText::FromString(FString::Printf(TEXT("플레이어 입장 대기중...: (%d/2)"), PlayerCount)));
	}
}
