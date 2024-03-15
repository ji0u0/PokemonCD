// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetSkill.h"

#include "Pokemon.h"
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

	// 내 Controller를 가져온다
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController) trainer = Cast<ATrainer>(PlayerController->GetPawn());
		
	else UE_LOG(LogTemp, Warning, TEXT("No Controller"));

}

void UWidgetSkill::SetSkillName(APokemon* pokemon)
{
	/*UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ESkill"), true);
	firstSkillName->SetText(EnumPtr->GetDisplayNameTextByIndex(static_cast<int32>(pokemon->pokemonSkill[0])));
	secondSkillName->SetText(EnumPtr->GetDisplayNameTextByIndex(static_cast<int32>(pokemon->pokemonSkill[1])));
	thirdSkillName->SetText(EnumPtr->GetDisplayNameTextByIndex(static_cast<int32>(pokemon->pokemonSkill[2])));
	fourthSkillName->SetText(EnumPtr->GetDisplayNameTextByIndex(static_cast<int32>(pokemon->pokemonSkill[3])));*/
	// firstSkillName->SetText(pokemon->SkillName(pokemon->firstSkill);
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
	trainer->CurrentPokemon->SkillEffect(trainer->CurrentPokemon->firstSkill);
	//몽타주 실행
	trainer->CurrentPokemon->PlayFirstSkillAnim();

	//this->SetVisibility(ESlateVisibility::Hidden);
	//trainer->SpawnedPokemon->firstSkill->Attack(trainer->oppoTrainer);
	//// SetVisibility(ESlateVisibility::Visible); 필요함

	//trainer->currentPokemon->firstSkill;

	
}

void UWidgetSkill::ClickSecondSkill()
{
	trainer->CurrentPokemon->SkillEffect(trainer->CurrentPokemon->secondSkill);
	////몽타주 실행
	trainer->CurrentPokemon->PlaySecondSkillAnim();

	//this->SetVisibility(ESlateVisibility::Hidden);
	//trainer->currentPokemon->secondSkill->Attack(trainer->oppoTrainer);
	//// SetVisibility(ESlateVisibility::Visible); 필요함
}

void UWidgetSkill::ClickThirdSkill()
{
	trainer->CurrentPokemon->SkillEffect(trainer->CurrentPokemon->thirdSkill);
	////몽타주 실행
	//ClickTOPlayAnim();

	//this->SetVisibility(ESlateVisibility::Hidden);
	//trainer->currentPokemon->thirdSkill->Attack(trainer->oppoTrainer);
	//// SetVisibility(ESlateVisibility::Visible); 필요함
}

void UWidgetSkill::ClickFourthSkill()
{
	////몽타주 실행
	//ClickTOPlayAnim();

	//this->SetVisibility(ESlateVisibility::Hidden);
	//trainer->currentPokemon->fourthSkill->Attack(trainer->oppoTrainer);
	//// SetVisibility(ESlateVisibility::Visible); 필요함
}

/*
void UWidgetSkill::ClickTOPlayAnim()
{
	/*auto anim = Cast<UTrainerAnimInstance>(trainer->TrainerSkelMeshComp->GetAnimInstance());
	anim->PlayCheeringMontage();#1#
}*/
