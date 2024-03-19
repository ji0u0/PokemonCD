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
	// ���� ���ϸ�
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
	// GameState ���� BeginPlay �ÿ� �� �� ������
	// ���� �Ϸ� ��ư�� ������ ������

	// main widget
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UWidgetMain> MainWidgetTemplate;

	UPROPERTY()
	class UWidgetMain* MainWidget;
	
	void CreateMainWidget();

	void SetVisibleMainWidget(bool bVisible);
	// ���ϸ��� Spawn�� �� ������
	// ���ϸ��� Destroy�Ǹ� ������

	// skill widget
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UWidgetSkill> SkillWidgetTemplate;

	UPROPERTY()
	class UWidgetSkill* SkillWidget;

	void CreateSkillWidget();

	void SetVisibleSkillWidget(bool bVisible);
	// ��ų�� �����ϴ� state�� �Ǹ� ������
	// ��ų�� �����ϸ� ������

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

};
