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

	// ���� �� �� ȣ�� (�ؾ���)
	UFUNCTION()
	void InitValue(UMainWidget* _main, int _id, FString text);

	// ��ư Ŭ�� �� ȣ��
	UFUNCTION()
	void OnClickButton();

	// ��ư�� �Ӽ� ������
	UPROPERTY()
	class UMainWidget* main;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 id;
};
