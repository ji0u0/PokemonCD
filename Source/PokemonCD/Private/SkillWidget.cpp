// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillWidget.h"

#include "MainWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void USkillWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SkillButton->OnClicked.AddDynamic(this, &USkillWidget::OnClickButton);
}

void USkillWidget::InitValue(UMainWidget* _main, int _id, FString text)
{
	this->main = _main;
	this->id = _id;
	SkillName->SetText(FText::FromString(FString(text)));
}

void USkillWidget::OnClickButton()
{
	UE_LOG(LogTemp, Log, TEXT("Click Skill Button"));
}
