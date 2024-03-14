// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PokemonGameMode.generated.h"


/**
 * 
 */
UCLASS()
class POKEMONCD_API APokemonGameMode : public AGameMode
{
	GENERATED_BODY()
	APokemonGameMode();
	virtual void StartPlay() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void PostLogin(APlayerController* NewPlayer) override;

public :

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ATrainer> PlayerTemplate;

	ATrainer* Authority;
	ATrainer* Autonomous;

	TArray<APlayerController*> ControllerArray;

	
	

	//<<<<<<< Updated upstream
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> LoadingUITemplate;

	UPROPERTY()
	class ULoadingUI* LoadingUI;

	// Main Widget
//=======
	// Choose Pokemon Widget
//>>>>>>> Stashed changes
	

	int32 tmp = 0;
private:
	
	void SetValue();

	void PossessPlayerCharacter(APlayerController* NewPlayer);
	void CheckPlayerLogin();
	void SpawnAuthority(APlayerController* NewPlayer);
	void SpawnAutonomous(APlayerController* NewPlayer);

public:
	FTransform AuthorityTransform;
	FTransform AutonomousProxyTransform;


	FVector AuthoritySpawnLoc;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FQuat AuthoritySpawnRotate;

	FVector AutonomousProxySpawnLoc;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FQuat AutonomousProxySpawnRotate;

	FVector PlayerScale;
};
