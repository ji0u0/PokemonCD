// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetSkill.h"

#include "Pokemon.h"
#include "PokemonWater.h"
#include "Skill.h"
#include "Trainer.h"
#include "TrainerAnimInstance.h"
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
	UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ESkill"), true);
	FText DisplayName = EnumPtr->GetDisplayNameTextByIndex(static_cast<int32>(Pokemon->firstSkill));
	firstSkillName->SetText(DisplayName);
	DisplayName = EnumPtr->GetDisplayNameTextByIndex(static_cast<int32>(Pokemon->secondSkill));
	secondSkillName->SetText(DisplayName);
	DisplayName = EnumPtr->GetDisplayNameTextByIndex(static_cast<int32>(Pokemon->thirdSkill));
	thirdSkillName->SetText(DisplayName);
	DisplayName = EnumPtr->GetDisplayNameTextByIndex(static_cast<int32>(Pokemon->fourthSkill));
	fourthSkillName->SetText(DisplayName);

	/*if(Pokemon->firstSkill)
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
	}*/
}

void UWidgetSkill::ClickSwapButton()
{
	/*trainer->currentPokemon->Destroy();

	FTimerHandle timerHandle;
	trainer->GetWorldTimerManager().SetTimer(timerHandle, [this]() {
			trainer->SpawnPokemon(trainer->currentPokemon);
		}, 1.f, false);*/
}

void UWidgetSkill::ClickFirstSkill()
{

	if (!trainer)	return;
	if (!trainer->CurrentPokemon)	return;
	auto myPokemon = trainer->CurrentPokemon;
	/*auto oppoPokemon = trainer->oppoTrainer.opp;*/

	myPokemon->Skill(myPokemon->firstSkill);
	////��Ÿ�� ����
	myPokemon->PlayFirstSkillAnim();

	//this->SetVisibility(ESlateVisibility::Hidden);
	//trainer->SpawnedPokemon->firstSkill->Attack(trainer->oppoTrainer);
	// SetVisibility(ESlateVisibility::Visible); �ʿ���

	//trainer->currentPokemon->firstSkill;
}

void UWidgetSkill::ClickSecondSkill()
{
	if (!trainer)	return;
	if (!trainer->CurrentPokemon)	return;
	trainer->CurrentPokemon->Skill(trainer->CurrentPokemon->secondSkill);
	//��Ÿ�� ����
	trainer->CurrentPokemon->PlaySecondSkillAnim();

	//this->SetVisibility(ESlateVisibility::Hidden);
	//trainer->currentPokemon->secondSkill->Attack(trainer->oppoTrainer);
	//// SetVisibility(ESlateVisibility::Visible); �ʿ���
}

void UWidgetSkill::ClickThirdSkill()
{
	trainer->CurrentPokemon->Skill(trainer->CurrentPokemon->thirdSkill);
	//��Ÿ�� ����
	trainer->CurrentPokemon->PlayThirdSkillAnim();

	//this->SetVisibility(ESlateVisibility::Hidden);
	//trainer->currentPokemon->thirdSkill->Attack(trainer->oppoTrainer);
	//// SetVisibility(ESlateVisibility::Visible); �ʿ���
}

void UWidgetSkill::ClickFourthSkill()
{
	trainer->CurrentPokemon->Skill(trainer->CurrentPokemon->thirdSkill);
	//��Ÿ�� ����
	trainer->CurrentPokemon->PlayThirdSkillAnim();

	//��Ÿ�� ����
	//ClickTOPlayAnim();

	//this->SetVisibility(ESlateVisibility::Hidden);
	//trainer->currentPokemon->fourthSkill->Attack(trainer->oppoTrainer);
	// SetVisibility(ESlateVisibility::Visible); �ʿ���
}

/*
void UWidgetSkill::ClickTOPlayAnim()
{
	/*auto anim = Cast<UTrainerAnimInstance>(trainer->TrainerSkelMeshComp->GetAnimInstance());
	anim->PlayCheeringMontage();#1#
}*/
