// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLobyPlayer.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"

// Sets default values
ATestLobyPlayer::ATestLobyPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
}

// Called when the game starts or when spawned
void ATestLobyPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestLobyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATestLobyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATestLobyPlayer::CreateSession()
{
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
	if(OnlineSub)
	{
		IOnlineSessionPtr SessionInterface;
		SessionInterface = OnlineSub->GetSessionInterface();
		if(SessionInterface.IsValid())
		{
			FOnlineSessionSettings SessionSettings;

			SessionSettings.bIsLANMatch = true;
			SessionSettings.bIsDedicated = false;
			SessionSettings.bAllowJoinInProgress = true;
			SessionSettings.bAllowInvites = true;

			SessionSettings.NumPublicConnections = 2;
			SessionSettings.NumPrivateConnections = 0;
			SessionSettings.bShouldAdvertise = true;

		}
	}

}

void ATestLobyPlayer::JoinSession()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("192.168.240.92"));
}

