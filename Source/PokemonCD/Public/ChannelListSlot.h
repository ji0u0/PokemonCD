// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChannelListSlot.generated.h"

/**
 * 
 */
UCLASS()
class POKEMONCD_API UChannelListSlot : public UUserWidget
{
	GENERATED_BODY()

public:
    UPROPERTY(meta = (BindWidget))
    class UButton* ButtonSessionName;
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* TextPlayerCount;
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* TextSessionName;
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* TextPing;

    UPROPERTY()
    int32 SessionSlotIndex;

protected:
    virtual void NativeConstruct() override;

private:
    UPROPERTY()
    class UPokemonCDGameInstance* ServerGameInstance;

    UFUNCTION()
    void OnClickJoinRoom();
};
