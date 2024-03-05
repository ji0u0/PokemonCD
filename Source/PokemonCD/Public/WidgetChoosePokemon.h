// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetChoosePokemon.generated.h"

/**
 * 
 */
UCLASS()
class POKEMONCD_API UWidgetChoosePokemon : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	// Bind Widget
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* completeButton;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* undoButton;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* Button_Sobble;

	// Trainer
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ATrainer> trainerFactory;

	UPROPERTY(EditDefaultsOnly)
	class ATrainer* trainer;

	UPROPERTY(EditDefaultsOnly)
	FVector trainerLoc = FVector(40.f, 1720.f, 190.f);
	FRotator trainerRot = FRotator(0.f, -90.f, 0.f);

	// Input Button
	UFUNCTION()
	void CompleteUI();

	UFUNCTION()
	void UndoSelect();

	UFUNCTION()
	void ChooseSobble();

	// Pokemon Factory
	UPROPERTY(EditAnywhere)
	TSubclassOf<class APokemonWater> sobbleFactory;

	// Keep Factory
	TSubclassOf<class APokemon> firstFactory = nullptr;
	TSubclassOf<class APokemon> secondFactory = nullptr;
	TSubclassOf<class APokemon> thirdFactory = nullptr;

	// location
	UPROPERTY(EditDefaultsOnly)
	FVector firstLoc = FVector(-1830.f, 1350.f, 150.f);

	UPROPERTY(EditDefaultsOnly)
	FVector secondLoc = FVector(-1830.f, 1050.f, 150.f);

	UPROPERTY(EditDefaultsOnly)
	FVector thirdLoc = FVector(-1830.f, 750.f, 150.f);
};
