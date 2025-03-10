// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuContextButton.h"
#include "StatsWidget.h"
#include "Blueprint/UserWidget.h"
#include "MenuContextWidget.generated.h"

/**
 * 
 */
UCLASS()
class SLASHER_API UMenuContextWidget : public UUserWidget
{
	GENERATED_BODY()


	UPROPERTY(meta = (BindWidget))
	UMenuContextButton* UseItemButton;
	UPROPERTY(meta = (BindWidget))
	UMenuContextButton* UseMagicButton;
	UPROPERTY(meta = (BindWidget))
	UMenuContextButton* EquipmentButton;
	UPROPERTY(meta = (BindWidget))
	UMenuContextButton* StatsButton;
	UPROPERTY(meta = (BindWidget))
	UMenuContextButton* DropItemButton;
	UPROPERTY(meta = (BindWidget))
	UMenuContextButton* OptionsButton;
	UPROPERTY(meta = (BindWidget))
	UMenuContextButton* ExitButton;

	UPROPERTY(meta = (BindWidget))
	UStatsWidget* StatsWidget;


	virtual FReply
	NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeConstruct() override;

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	                                  UDragDropOperation*& OutOperation) override;

	void HandleNativeVisibilityChanged(ESlateVisibility InVisibility);
};
