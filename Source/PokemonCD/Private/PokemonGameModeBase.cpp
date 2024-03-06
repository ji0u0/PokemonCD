// Fill out your copyright notice in the Description page of Project Settings.


#include "PokemonGameModeBase.h"

#include "LoadingUI.h"
#include "MainWidget.h"
#include "Blueprint/UserWidget.h"
#include "WidgetChoosePokemon.h"


void APokemonGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	/*LoadingUI = CreateWidget<ULoadingUI>(GetWorld(), LoadingUITemplate);
	LoadingUI->AddToViewport();*/



	// Main Widget 생성
	// mainWidget = CreateWidget<UMainWidget>(GetWorld(), UMainWidget::StaticClass());
	//mainWidget = CreateWidget<UMainWidget>(GetWorld(), mainWidgetFactory); // Factory는 대체 왜 필요한 것인가

	//if (mainWidget != nullptr)
	//{
	//	// Main Widget 표시
	//	mainWidget->AddToViewport();
	//}

	//if (APlayerController* playerController = GetWorld()->GetFirstPlayerController())
	//{
	//	playerController->bShowMouseCursor = true;
	//}

	// UI only (고쳐야 함)
	/*APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		FInputModeUIOnly InputMode;
		InputMode.SetWidgetToFocus(/* 여기에 포커스를 설정할 UI 위젯을 넣어줍니다 #1#);
		PlayerController->SetInputMode(InputMode);
	}*/
	CreateChooseWidget();
}

void APokemonGameModeBase::CreateChooseWidget()
{
	// Choose Pokemon Widget
	chooseWidget = CreateWidget<UWidgetChoosePokemon>(GetWorld(), chooseWidgetFactory);

	if (chooseWidget != nullptr)
	{
		chooseWidget->AddToViewport();
	}

	// 마우스 표시
	if (APlayerController* playerController = GetWorld()->GetFirstPlayerController())
	{
		playerController->bShowMouseCursor = true;
	}
}
