// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TrainerPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "WidgetChoosePokemon.generated.h"

const int SWITCHER_INDEX_SELECTPOKEMON = 0;
const int SWITCHER_INDEX_Wating = 1;

/**
 * 
 */
UCLASS()
class POKEMONCD_API UWidgetChoosePokemon : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;
	
public:

	UPROPERTY()
	class APokemonGameMode* GameMode;

	UPROPERTY()
	class APokemonGameState* GameState;

	UPROPERTY()
	class ATrainerPlayerController* pc;

	// Bind Widget
	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UWidgetSwitcher* ChooseCanvasSwitcher;*/
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* Button_Rabifoot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* Button_Sobble;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* Button_Grookey;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* completeButton;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* undoButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* txt_firstpokemon;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* txt_secondpokemon;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* txt_thirdpokemon;

	//// Trainer
	//UPROPERTY(EditAnywhere)
	//TSubclassOf<class ATrainer> trainerFactory;

	UPROPERTY(EditDefaultsOnly)
	class ATrainer* trainer;

	UPROPERTY(EditDefaultsOnly)
	class ATrainerPlayerController* _PlayerController;

	UPROPERTY(EditDefaultsOnly)
	FVector trainerLoc = FVector(40.f, 1720.f, 190.f);
	FRotator trainerRot = FRotator(0.f, -90.f, 0.f);

	// Input Button
	/*UFUNCTION()
	void SelectComplete();

	UFUNCTION()
	void SpawnOrder();*/

	UFUNCTION()
	void UndoSelect();
	void CompleteUI();

	UFUNCTION()
	void ChooseRabifoot();
	UFUNCTION()
	void ChooseSobble();
	UFUNCTION()
	void ChooseGrookey();

	UFUNCTION()
	void SelectedPokemon();

	// Pokemon Factory
	UPROPERTY(EditAnywhere)
	TSubclassOf<class APokemonWater> sobbleFactory;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class APokemonFire> scorbunnyFactory;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class APokemonGrass> grookeyFactory;

	// Keep Factory
	TArray<EPokemonList> PokemonLists = {
		EPokemonList::Default,
		EPokemonList::Default,
		EPokemonList::Default
	};

	int32 index = 0;

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
