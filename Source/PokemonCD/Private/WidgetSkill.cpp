// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetSkill.h"

#include "Pokemon.h"
#include "Skill.h"
#include "Trainer.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UWidgetSkill::NativeConstruct()
{
	Super::NativeConstruct();

	SwapButton->OnClicked.AddDynamic(this, &UWidgetSkill::ClickSwapButton);
	firstSkill->OnClicked.AddDynamic(this, &UWidgetSkill::ClickFirstSkill);
	secondSkill->OnClicked.AddDynamic(this, &UWidgetSkill::ClickSecondSkill);
	thirdSkill->OnClicked.AddDynamic(this, &UWidgetSkill::ClickThirdSkill);
	fourthSkill->OnClicked.AddDynamic(this, &UWidgetSkill::ClickFourthSkill);

	// �� Controller�� �����´�
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController) trainer = Cast<ATrainer>(PlayerController->GetPawn());
		
	else UE_LOG(LogTemp, Warning, TEXT("No Controller"));

}

void UWidgetSkill::SetSkillName(APokemon* Pokemon)
{
	if(Pokemon->firstSkill)
	{
		firstSkillName->SetText(FText::FromString(Pokemon->firstSkill->skillName));
	}
	if(Pokemon->secondSkill)
	{
		secondSkillName->SetText(FText::FromString(Pokemon->secondSkill->skillName));
	}
	if(Pokemon->thirdSkill)
	{
		thirdSkillName->SetText(FText::FromString(Pokemon->thirdSkill->skillName));
	}
	if(Pokemon->fourthSkill)
	{
		fourthSkillName->SetText(FText::FromString(Pokemon->fourthSkill->skillName));
	}
}

void UWidgetSkill::ClickSwapButton()
{
	trainer->currentPokemon->Destroy();

	FTimerHandle timerHandle;
	trainer->GetWorldTimerManager().SetTimer(timerHandle, [this]() {
			trainer->SpawnPokemon(trainer->currentPokemon);
		}, 1.f, false);
}

void UWidgetSkill::ClickFirstSkill()
{
	this->SetVisibility(ESlateVisibility::Hidden);
	trainer->currentPokemon->firstSkill->Attack(trainer->oppoTrainer);
	// SetVisibility(ESlateVisibility::Visible); �ʿ���
}

void UWidgetSkill::ClickSecondSkill()
{
	this->SetVisibility(ESlateVisibility::Hidden);
	trainer->currentPokemon->secondSkill->Attack(trainer->oppoTrainer);
	// SetVisibility(ESlateVisibility::Visible); �ʿ���
}

void UWidgetSkill::ClickThirdSkill()
{
	this->SetVisibility(ESlateVisibility::Hidden);
	trainer->currentPokemon->thirdSkill->Attack(trainer->oppoTrainer);
	// SetVisibility(ESlateVisibility::Visible); �ʿ���
}

void UWidgetSkill::ClickFourthSkill()
{
	this->SetVisibility(ESlateVisibility::Hidden);
	trainer->currentPokemon->fourthSkill->Attack(trainer->oppoTrainer);
	// SetVisibility(ESlateVisibility::Visible); �ʿ���
}
