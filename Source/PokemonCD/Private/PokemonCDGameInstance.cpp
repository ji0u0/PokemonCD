// Fill out your copyright notice in the Description page of Project Settings.


#include "PokemonCDGameInstance.h"
#include "OnlineSessionSettings.h"
#include "Online/OnlineSessionNames.h"
#include "OnlineSubsystem.h"
#include "Kismet/GameplayStatics.h"

UPokemonCDGameInstance::UPokemonCDGameInstance()
{
	
}

void UPokemonCDGameInstance::OpenLobby()
{
	UWorld* World = GetWorld();
	if(World)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString::Printf(TEXT("OpenLobby ")));
		World->ServerTravel("/Game/Maps/LV_LobyMap?listen");
	}
}

void UPokemonCDGameInstance::CallOpenLevel(const FString& Address)
{
	APlayerController* PlayerController = GetWorld()->GetGameInstance()->GetFirstLocalPlayerController();
	if (PlayerController)
	{
		PlayerController->ClientTravel(Address, TRAVEL_Absolute);
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString::Printf(TEXT("Get PlayerController ")));
	}
}

void UPokemonCDGameInstance::ServerTravel()
{
	UWorld* World = GetWorld();
	if (World)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString::Printf(TEXT("ServerTravel ")));
		World->ServerTravel("/Game/Maps/LV_ToTal");
	}
}



