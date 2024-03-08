// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Pokemon.generated.h"

UENUM(BlueprintType)
enum class Type : uint8
{
	Normal UMETA(DisplayName = "Nrass"),
	Grass UMETA(DisplayName = "Grass"),
	Fire UMETA(DisplayName = "Fire"),
	Water UMETA(DisplayName = "Water")
};

UCLASS()
class POKEMONCD_API APokemon : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APokemon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float timeDeltaTime;

	UPROPERTY(EditDefaultsOnly)
	class ATrainer* OwnedTrainer;

	///// status /////
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FString pokemonName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	Type pokemonType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int pokemonMaxHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int pokemonCurHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float pokemonAttack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float pokemonDefense;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float pokemonSpeed;

	///// Skill /////
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class USkill* firstSkill;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class USkill* secondSkill;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class USkill* thirdSkill;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class USkill* fourthSkill;

};
