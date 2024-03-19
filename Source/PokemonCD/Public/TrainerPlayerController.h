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
	///// Pokemon /////
	// 현재 포켓몬
	UPROPERTY(Replicated, EditDefaultsOnly)
	EPokemonList Pokemon = EPokemonList::GROOKEY;

	// void SetPokemon(EPokemonList Selected);

	///// Widget /////
	// choose pokemon widget
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UWidgetChoosePokemon> PokemonTemplate;

	UPROPERTY()
	class UWidgetChoosePokemon* PokemonWidget;

	void CreatePokemonWidget();

	void SetVisiblePokemonWidget(bool bVisible);
	// GameState 에서 BeginPlay 시에 한 번 켜진다
	// 선택 완료 버튼을 누르면 꺼진다

	// main widget
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UWidgetMain> MainWidgetTemplate;

	UPROPERTY()
	class UWidgetMain* MainWidget;
	
	void CreateMainWidget();

	void SetVisibleMainWidget(bool bVisible);
	// 포켓몬이 Spawn될 때 켜진다
	// 포켓몬이 Destroy되면 꺼진다

	// skill widget
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UWidgetSkill> SkillWidgetTemplate;

	UPROPERTY()
	class UWidgetSkill* SkillWidget;

	void CreateSkillWidget();

	void SetVisibleSkillWidget(bool bVisible);
	// 스킬을 선택하는 state가 되면 켜진다
	// 스킬을 선택하면 꺼진다

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

};
