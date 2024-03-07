// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"

#include "StatusWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"


void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// My Status 추가
	myStatusWidget = CreateWidget<UStatusWidget>(GetWorld(), statusWidgetFactory);
	UCanvasPanelSlot* MyStatusSlot = MyStatus->AddChildToCanvas(myStatusWidget);
	MyStatusSlot->SetSize(FVector2D(360, 240));

	// Opponent Status 추가
	oppoStatusWidget = CreateWidget<UStatusWidget>(GetWorld(), statusWidgetFactory);
	UCanvasPanelSlot* OpponentStatusSlot = OpponentStatus->AddChildToCanvas(oppoStatusWidget);
	OpponentStatusSlot->SetSize(FVector2D(360, 240));
}
