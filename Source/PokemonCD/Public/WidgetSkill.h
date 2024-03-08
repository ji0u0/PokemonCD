// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetSkill.generated.h"

/**
 * 
 */

class APokemon;
DECLARE_DELEGATE_OneParam(FStringDelegate, FString);


UCLASS()
class POKEMONCD_API UWidgetSkill : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	/*UPROPERTY(EditDefaultsOnly)
	class APlayerController* pc;*/

	UPROPERTY(EditDefaultsOnly)
	class ATrainer* trainer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* SwapButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* firstSkill;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* secondSkill;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* thirdSkill;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* fourthSkill;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* firstSkillName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* secondSkillName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* thirdSkillName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* fourthSkillName;

	void SetSkillName(APokemon* Pokemon);

	UFUNCTION()
	void ClickSwapButton();

	UFUNCTION()
	void ClickFirstSkill();

	UFUNCTION()
	void ClickSecondSkill();

	UFUNCTION()
	void ClickThirdSkill();

	UFUNCTION()
	void ClickFourthSkill();

	//애니메이션(응원) 실행 - 트레이너
	void ClickTOPlayAnimTrainer();

	UPROPERTY(EditDefaultsOnly)
	bool isFirstAttack;
};
