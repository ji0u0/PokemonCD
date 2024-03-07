// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetMain.h"

#include "WidgetStatus.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/CanvasPanel.h"

void UWidgetMain::NativeConstruct()
{
	Super::NativeConstruct();

	// My Status 추가
	myStatus = CreateWidget<UWidgetStatus>(GetWorld(), statusWidgetFactory);
	UCanvasPanelSlot* MyStatusSlot = MyStatusPanel->AddChildToCanvas(myStatus);
	MyStatusSlot->SetSize(FVector2D(360, 240));

	// Opponent Status 추가
	oppoStatus = CreateWidget<UWidgetStatus>(GetWorld(), statusWidgetFactory);
	UCanvasPanelSlot* OpponentStatusSlot = OpponentStatusPanel->AddChildToCanvas(oppoStatus);
	OpponentStatusSlot->SetSize(FVector2D(360, 240));
}
