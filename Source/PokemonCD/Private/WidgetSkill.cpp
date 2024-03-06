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

	firstSkill->OnClicked.AddDynamic(this, &UWidgetSkill::ClickFirstSkill);
	secondSkill->OnClicked.AddDynamic(this, &UWidgetSkill::ClickSecondSkill);
	thirdSkill->OnClicked.AddDynamic(this, &UWidgetSkill::ClickThirdSkill);
	fourthSkill->OnClicked.AddDynamic(this, &UWidgetSkill::ClickFourthSkill);

	// 내 Controller를 가져온다
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)	trainer = Cast<ATrainer>(PlayerController->GetPawn());
	else UE_LOG(LogTemp, Warning, TEXT("No Controller"));

}

void UWidgetSkill::SetSkillName(FString first, FString second, FString third, FString fourth)
{
	firstSkillName->SetText(FText::FromString(first));
	secondSkillName->SetText(FText::FromString(second));
	thirdSkillName->SetText(FText::FromString(third));
	fourthSkillName->SetText(FText::FromString(fourth));
}

void UWidgetSkill::ClickFirstSkill()
{
	trainer->currentPokemon->firstSkill->Attack(trainer->oppoTrainer);
}

void UWidgetSkill::ClickSecondSkill()
{
	trainer->currentPokemon->secondSkill->Attack(trainer->oppoTrainer);
}

void UWidgetSkill::ClickThirdSkill()
{
	trainer->currentPokemon->thirdSkill->Attack(trainer->oppoTrainer);
}

void UWidgetSkill::ClickFourthSkill()
{
	trainer->currentPokemon->fourthSkill->Attack(trainer->oppoTrainer);
}
