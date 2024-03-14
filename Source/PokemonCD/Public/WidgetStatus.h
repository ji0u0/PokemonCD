// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetStatus.generated.h"

/**
 * 
 */
UCLASS()
class POKEMONCD_API UWidgetStatus : public UUserWidget
{
	GENERATED_BODY()

public:
	// bind widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* PokemonName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* HealthBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UHorizontalBox* PokeballBox;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> normalBallFactory;

	UPROPERTY(BlueprintReadOnly)
	class UUserWidget* normalBallImage;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> noneBallFactory;

	UPROPERTY(BlueprintReadOnly)
	class UUserWidget* noneBallImage;

	void NativeConstruct() override;

	//void SetPokeballBox(ATrainer* trainer);
};
