// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TrainerPlayerController.generated.h"


UENUM()
enum class _EPokemonList : uint8
{
	RABIFOOT,
	SOBBLE,
	GROOKEY
};
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


	UPROPERTY(EditDefaultsOnly)
	_EPokemonList Pokemon;

	void SetPokemon(_EPokemonList Selected);

	void UseSkill();

};
