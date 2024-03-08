// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AutonomousPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class POKEMONCD_API AAutonomousPlayerController : public APlayerController
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

public:
	UPROPERTY()
	class APokemonGameMode* GameMode;

	void CheckRoleAndPossess();
};
