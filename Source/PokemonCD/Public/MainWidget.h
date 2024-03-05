// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class POKEMONCD_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	// Bind Widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UCanvasPanel* MyStatus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UCanvasPanel* OpponentStatus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UVerticalBox* SkillBox;

	// Status Widget
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> statusWidgetFactory;
	
	UPROPERTY(BlueprintReadOnly)
	class UStatusWidget* myStatusWidget;

	UPROPERTY(BlueprintReadOnly)
	class UStatusWidget* oppoStatusWidget;

	// Horizontal Box
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> skillWidgetFactory;

	UPROPERTY(BlueprintReadOnly)
	class USkillWidget* skillWidget;
};
