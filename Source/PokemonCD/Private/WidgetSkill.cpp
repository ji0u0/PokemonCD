// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetSkill.h"

#include "Pokemon.h"
#include "PokemonGameState.h"
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

	// 내 Controller를 가져온다
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		trainer = Cast<ATrainer>(PlayerController->GetPawn());
	}

	else UE_LOG(LogTemp, Warning, TEXT("No Controller"));

	GameState = GetWorld()->GetGameState<APokemonGameState>();
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
	if (_TrainerPlayerController && trainer->IsLocallyControlled())
	{
		if (trainer->HasAuthority())
		{
			GameState->AuthoritySelectSkill = true;
			GameState->FOnAuthoritySelectSkill.BindDynamic(this, &UWidgetSkill::ExcuteFirstSkill);
		}
		else
		{
			GameState->AutonomousSelectSkill = true;
			GameState->FOnAutonomousSelectSkill.BindDynamic(this, &UWidgetSkill::ExcuteFirstSkill);
		}
	}
}

void UWidgetSkill::ClickSecondSkill()
{
	if (_TrainerPlayerController && trainer->IsLocallyControlled())
	{
		if (trainer->HasAuthority())
		{
			GameState->AuthoritySelectSkill = true;
			GameState->FOnAuthoritySelectSkill.BindDynamic(this, &UWidgetSkill::ExcuteSecondSkill);
		}
		else
		{
			GameState->AutonomousSelectSkill = true;
			GameState->FOnAutonomousSelectSkill.BindDynamic(this, &UWidgetSkill::ExcuteSecondSkill);
		}
	}
}

void UWidgetSkill::ClickThirdSkill()
{
	if (_TrainerPlayerController && trainer->IsLocallyControlled())
	{
		if (trainer->HasAuthority())
		{
			GameState->AuthoritySelectSkill = true;
			GameState->FOnAuthoritySelectSkill.BindDynamic(this, &UWidgetSkill::ExcuteThirdSkill);
		}
		else
		{
			GameState->AutonomousSelectSkill = true;
			GameState->FOnAutonomousSelectSkill.BindDynamic(this, &UWidgetSkill::ExcuteThirdSkill);
		}
	}
}

void UWidgetSkill::ClickFourthSkill()
{
	if (_TrainerPlayerController && trainer->IsLocallyControlled())
	{
		if (trainer->HasAuthority())
		{
			GameState->AuthoritySelectSkill = true;
			GameState->FOnAuthoritySelectSkill.BindDynamic(this, &UWidgetSkill::ExcuteFourthSkill);
		}
		else
		{
			GameState->AutonomousSelectSkill = true;
			GameState->FOnAutonomousSelectSkill.BindDynamic(this, &UWidgetSkill::ExcuteFourthSkill);
		}
	}
}

void UWidgetSkill::ExcuteFirstSkill()
{
	auto myPokemon = trainer->CurrentPokemon;
	/*auto oppoPokemon = trainer->oppoTrainer.opp;*/

	myPokemon->Skill(myPokemon->firstSkill);
	//몽타주 실행
	myPokemon->PlayFirstSkillAnim();
	//공격 데미지 계산 실행
	/*currPokemon->OnMyAttack()*/

	//this->SetVisibility(ESlateVisibility::Hidden);
	//trainer->SpawnedPokemon->firstSkill->Attack(trainer->oppoTrainer);
	// SetVisibility(ESlateVisibility::Visible); 필요함

	//trainer->currentPokemon->firstSkill;

	GameState->FOnAuthoritySelectSkill.Unbind();

	GEngine->AddOnScreenDebugMessage(-1, 30, FColor::Red, TEXT("UWidgetSkill::ExcuteFirstSkill"));

}

void UWidgetSkill::ExcuteSecondSkill()
{
	UE_LOG(LogTemp, Warning, TEXT("SecondSkillAllowd"));
	trainer->CurrentPokemon->Skill(trainer->CurrentPokemon->secondSkill);
	//몽타주 실행
	trainer->CurrentPokemon->PlaySecondSkillAnim();

	//this->SetVisibility(ESlateVisibility::Hidden);
	//trainer->currentPokemon->secondSkill->Attack(trainer->oppoTrainer);
	//// SetVisibility(ESlateVisibility::Visible); 필요함

	GameState->FOnAuthoritySelectSkill.Unbind();
	//autonomous도 언바인딩해주기...
	GEngine->AddOnScreenDebugMessage(-1, 30, FColor::Red, TEXT("UWidgetSkill::ExcuteSecondSkill"));

}

void UWidgetSkill::ExcuteThirdSkill()
{
	trainer->CurrentPokemon->Skill(trainer->CurrentPokemon->thirdSkill);
	//몽타주 실행
	trainer->CurrentPokemon->PlayThirdSkillAnim();

	//this->SetVisibility(ESlateVisibility::Hidden);
	//trainer->currentPokemon->thirdSkill->Attack(trainer->oppoTrainer);
	//// SetVisibility(ESlateVisibility::Visible); 필요함
	///
	GameState->FOnAuthoritySelectSkill.Unbind();
	GEngine->AddOnScreenDebugMessage(-1, 30, FColor::Red, TEXT("UWidgetSkill::ExcuteThirdSkill"));

}

void UWidgetSkill::ExcuteFourthSkill()
{
	trainer->CurrentPokemon->Skill(trainer->CurrentPokemon->thirdSkill);
	//몽타주 실행
	trainer->CurrentPokemon->PlayThirdSkillAnim();

	//몽타주 실행
	//ClickTOPlayAnim();

	//this->SetVisibility(ESlateVisibility::Hidden);
	//trainer->currentPokemon->fourthSkill->Attack(trainer->oppoTrainer);
	// SetVisibility(ESlateVisibility::Visible); 필요함

	GameState->FOnAuthoritySelectSkill.Unbind();

	GEngine->AddOnScreenDebugMessage(-1, 30, FColor::Red, TEXT("UWidgetSkill::ExcuteFourthSkill"));
}


/*
void UWidgetSkill::ClickTOPlayAnim()
{
	/*auto anim = Cast<UTrainerAnimInstance>(trainer->TrainerSkelMeshComp->GetAnimInstance());
	anim->PlayCheeringMontage();#1#
}*/
