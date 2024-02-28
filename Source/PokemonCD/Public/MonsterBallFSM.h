// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MonsterBallFSM.generated.h"

//UENUM(BlueprintType)
//enum class EMonsterBallState : uint8
//{
//	IDLE		UMETA(DisplayName = "IDLE")
//	THROWED		UMETA(DisplayName = "THROWED")
//	SPAWN		UMETA(DisplayNmae = "SPAWN")
//	
//
//};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POKEMONCD_API UMonsterBallFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMonsterBallFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	//UPROPERTY(EditAnywhere)
	//EMonsterBallState State;
};
