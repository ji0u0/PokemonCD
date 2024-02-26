// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"

#include "MainStatusWidget.h"
#include "Components/CanvasPanel.h"


void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// statusWidget 생성
	statusWidget = CreateWidget<UMainStatusWidget>(GetWorld(), statusWidgetFactory);

	// My Status 추가
	MyStatus->AddChildToCanvas(statusWidget);

	// statusWidget 생성
	statusWidget = CreateWidget<UMainStatusWidget>(GetWorld(), statusWidgetFactory);

	// Opponent Status 추가
	OpponentStatus->AddChildToCanvas(statusWidget);
}
