// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/StatsWidget.h"

#include "Character/SlasherCharacter.h"
#include "Modes/SlasherGameInstance.h"
#include "Kismet/GameplayStatics.h"


void UStatsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	OnNativeVisibilityChanged.AddUObject(this, &UStatsWidget::HandleNativeVisibilityChanged);
	//Define Base Text Values
	HPTextBlock->SetText(FText::FromString("HP ITEM"));
	MPTextBlock->SetText(FText::FromString("MP"));
	GuardTextBlock->SetText(FText::FromString("GUARD"));
	ExperienceTextBlock->SetText(FText::FromString("EXPERIENCE"));
	LevelTextBlock->SetText(FText::FromString("LEVEL"));
	StatusTextBlock->SetText(FText::FromString("STATUS"));
	GoldTextBlock->SetText(FText::FromString("GOLD"));
}

FReply UStatsWidget::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);

	return FReply::Handled();
}

FReply UStatsWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	return FReply::Unhandled();
}


void UStatsWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
}

void UStatsWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
}

void UStatsWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
                                        UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
}

void UStatsWidget::HandleNativeVisibilityChanged(ESlateVisibility InVisibility)
{
	StatsWidget_UpdateAll();
}

void UStatsWidget::StatsWidget_UpdateAll()
{
	USlasherGameInstance* SlasherGI = Cast<USlasherGameInstance>(GetGameInstance());
	ASlasherCharacter* PlayerCharacter = Cast<ASlasherCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (PlayerCharacter)
	{
		//Set HP
		FString DisplayHP = FString::SanitizeFloat(PlayerCharacter->CurrentHealth, 0);
		HPDisplayTextBlock->SetText(FText::FromString(DisplayHP));
		//Set Mana
		FString DisplayMP = FString::SanitizeFloat(PlayerCharacter->CurrentMana, 0);
		MPDisplayTextBlock->SetText(FText::FromString(DisplayMP));

		//Set Experience
		FString DisplayExp = FString::SanitizeFloat(SlasherGI->GI_CurrentExperience, 0);
		ExperienceDisplayTextBlock->SetText(FText::FromString(DisplayExp));

		//Set Level
		FString DisplayLevel = FString::FromInt(SlasherGI->GI_CurrentLevel);
		LevelDisplayTextBlock->SetText(FText::FromString(DisplayLevel));

		//SetStatus
		//Not implemented


		//SetGold
		FString DisplayGold = FString::FromInt(SlasherGI->Gold);
		GoldDisplayTextBlock->SetText(FText::FromString(DisplayGold));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(0, 20.f, FColor::Red,
		                                 "StatsWidget.cpp - Player Character is NOT VALID from Stats Window Update");
	}
}
