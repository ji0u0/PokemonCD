// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyServerWidget.generated.h"

/**
 * 
 */
UCLASS()
class POKEMONCD_API ULobbyServerWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* CreateSessionButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* JoinSessionButton;

	UFUNCTION()
	void CreateSession();
	UFUNCTION()
	void JoinSession();
};
