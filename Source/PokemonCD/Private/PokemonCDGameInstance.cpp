// Fill out your copyright notice in the Description page of Project Settings.


#include "PokemonCDGameInstance.h"

#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "Kismet/GameplayStatics.h"

void UPokemonCDGameInstance::CreateSession()
{
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub)
	{
		SessionInterface = OnlineSub->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			FOnlineSessionSettings SessionSettings;

			SessionSettings.bIsLANMatch = true;
			SessionSettings.bIsDedicated = false;
			SessionSettings.bAllowJoinInProgress = true;
			SessionSettings.bAllowInvites = true;

			SessionSettings.NumPublicConnections = 2;
			SessionSettings.NumPrivateConnections = 0;
			SessionSettings.bShouldAdvertise = true;

			SessionInterface->CreateSession(0, "HostSession", SessionSettings);
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT(" CreateSession")); // 화면출력
		}
	}
}

void UPokemonCDGameInstance::JoinSession()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("192.168.240.92"));
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT(" JoinSession")); // 화면출력
}
