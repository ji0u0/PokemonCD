// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillWidget.generated.h"

/**
 * 
 */
UCLASS()
class POKEMONCD_API USkillWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	// bind widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* SkillButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* SkillName;

	// 시작 할 때 호출 (해야함)
	UFUNCTION()
	void InitValue(UMainWidget* _main, int _id, FString text);

	// 버튼 클릭 시 호출
	UFUNCTION()
	void OnClickButton();

	// 버튼의 속성 데이터
	UPROPERTY()
	class UMainWidget* main;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 id;
};
