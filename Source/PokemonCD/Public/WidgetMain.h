// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetMain.generated.h"

class APokemon;
/**
 * 
 */
UCLASS()
class POKEMONCD_API UWidgetMain : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly)
	class ATrainer* trainer;

	// Bind Widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UCanvasPanel* MyStatusPanel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UCanvasPanel* OpponentStatusPanel;

	// Status Widget
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UWidgetStatus> statusWidgetFactory;

	UPROPERTY(BlueprintReadOnly)
	class UWidgetStatus* myStatus;

	UPROPERTY(BlueprintReadOnly)
	class UWidgetStatus* oppoStatus;

	UFUNCTION()
	void SetStatus();
};
