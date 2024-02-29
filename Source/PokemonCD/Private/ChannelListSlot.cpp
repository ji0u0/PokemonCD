// Fill out your copyright notice in the Description page of Project Settings.


#include "ChannelListSlot.h"
#include "PokemonCDGameInstance.h"
#include "Components/Button.h"


void UChannelListSlot::NativeConstruct()
{
    Super::NativeConstruct();

    ServerGameInstance = Cast<UPokemonCDGameInstance>(GetGameInstance());

    //binding Session Name Button to Join Room function
    ButtonSessionName->OnClicked.AddDynamic(this, &UChannelListSlot::OnClickJoinRoom);
}

void UChannelListSlot::OnClickJoinRoom()
{
    if (ServerGameInstance) {
        ServerGameInstance->JoinMySession(SessionSlotIndex);
    }
}
