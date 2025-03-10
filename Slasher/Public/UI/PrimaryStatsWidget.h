// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "PrimaryStatsWidget.generated.h"

/**
 * 
 */
UCLASS()
class SLASHER_API UPrimaryStatsWidget : public UUserWidget
{
	GENERATED_BODY()

	//HP Display
	UPROPERTY(meta = (BindWidget))
	UTextBlock* HPTextBlock;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Display_HPTextBlock;

	//Guard
	UPROPERTY(meta = (BindWidget))
	UTextBlock* GuardTextBlock;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Display_GuardTextBlock;

	//MP Display
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MPTextBlock;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Display_MPTextBlock;

	//Attack
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DamageTextBlock;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MagicDmgModTextBlock;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* AttackSpeedTextBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Display_DamageTextBlock;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Display_MagicDmgModTextBlock;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Display_AttackSpeedTextBlock;

	//Attributes
	UPROPERTY(meta = (BindWidget))
	UTextBlock* StrengthTextBlock;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Display_Strength;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* StaminaTextBlock;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Display_StaminaTextBlock;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DexterityTextBlock;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Display_DexterityTextBlock;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* IntelligenceTextBlock;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Display_Intelligence;


	//Defenses
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ArmorTextBlock;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ResistFireTextBlock;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ResistColdTextBlock;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ResistDetrimentalTextBlock;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ResistDivineTextBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Display_ArmorTextBlock;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Display_ResistFireTextBlock;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Display_ResistColdTextBlock;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Display_ResistDetrimentalTextBlock;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Display_ResistDivineTextBlock;


	//Experience Display
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ExperienceTextBlock;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Display_ExperienceTextBlock;

	//Level Display
	UPROPERTY(meta = (BindWidget))
	UTextBlock* LevelTextBlock;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Display_LevelTextBlock;

	//Status Display
	UPROPERTY(meta = (BindWidget))
	UTextBlock* StatusTextBlock;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Display_StatusTextBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* GoldTextBlock;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Display_GoldTextBlock;

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
	void PrimaryStatsWidget_UpdateAll();
};
