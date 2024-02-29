// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PokemonGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class POKEMONCD_API APokemonGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> LoadingUITemplate;

	UPROPERTY()
	class ULoadingUI* LoadingUI;

	// Main Widget
	UPROPERTY(EditDefaultsOnly)
	// TSubclassOf<class UMainWidget> mainWidgetFactory;
	TSubclassOf<class UUserWidget> mainWidgetFactory;
	
	UPROPERTY(BlueprintReadOnly)
	// class UMainWidget* mainWidget;
	class UUserWidget* mainWidget;
	
};
