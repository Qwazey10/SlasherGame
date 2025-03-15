// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "StatsWidget.generated.h"

/**
 * 
 */
UCLASS()
class SLASHER_API UStatsWidget : public UUserWidget
{
	GENERATED_BODY()


	//HP Display
	UPROPERTY(meta = (BindWidget))
	UTextBlock* HPTextBlock;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* HPDisplayTextBlock;

	//Guard
	UPROPERTY(meta = (BindWidget))
	UTextBlock* GuardTextBlock;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* GuardDisplayTextBlock;

	//MP Display
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MPTextBlock;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MPDisplayTextBlock;

	//Experience Display
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ExperienceTextBlock;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ExperienceDisplayTextBlock;

	//Level Display
	UPROPERTY(meta = (BindWidget))
	UTextBlock* LevelTextBlock;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* LevelDisplayTextBlock;

	//Status Display
	UPROPERTY(meta = (BindWidget))
	UTextBlock* StatusTextBlock;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* StatusDisplayTextBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* GoldTextBlock;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* GoldDisplayTextBlock;

	//Images
	UPROPERTY(meta = (BindWidget))
	UImage* BackgroundImage;
	UPROPERTY(meta = (BindWidget))
	UImage* ForegroundImage;

	virtual FReply
	NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeConstruct() override;

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	                                  UDragDropOperation*& OutOperation) override;

	void HandleNativeVisibilityChanged(ESlateVisibility InVisibility);

public:
	void StatsWidget_UpdateAll();
};
