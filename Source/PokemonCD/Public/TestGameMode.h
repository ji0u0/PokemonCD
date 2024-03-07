// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestLobyPlayer.h"
#include "GameFramework/GameMode.h"
#include "TestGameMode.generated.h"

/**
 *
 */
UCLASS()
class POKEMONCD_API ATestGameMode : public AGameMode
{
	GENERATED_BODY()
	ATestGameMode();
	virtual void BeginPlay() override;

public:

	void SpawnPlayerCharacter();
	void SetValue();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ATestLobyPlayer> LobbyPlayerTemplate;

	FTransform AuthorityTransform;
	FTransform AutonomousProxyTransform;


	FVector AuthoritySpawnLoc;
	FQuat AuthoritySpawnRotate;

	FVector AutonomousProxySpawnLoc;
	FQuat AutonomousProxySpawnRotate;

	FVector PlayerScale;
};