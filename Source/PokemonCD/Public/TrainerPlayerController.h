// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PokemonCD.h"
#include "GameFramework/PlayerController.h"
#include "TrainerPlayerController.generated.h"


/**
 * 
 */
UCLASS()
class POKEMONCD_API ATrainerPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UWidgetChoosePokemon> PokemonTemplate;

	UPROPERTY()
	class UWidgetChoosePokemon* PokemonChoose;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UWidgetMain> MainWidgetTemplate;

	UPROPERTY()
	class UWidgetMain* MainWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UWidgetSkill> SkillWidgetTemplate;

	UPROPERTY()
	class UWidgetSkill* SkillWidget;

	UPROPERTY(Replicated, EditDefaultsOnly)
	EPokemonList Pokemon = EPokemonList::GROOKEY;

	void SetPokemon(EPokemonList Selected);

	void UseSkill();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

};
